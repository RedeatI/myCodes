import cv2
import os
import json
from tqdm import tqdm
import numpy as np

provinces = ["皖", "沪", "津", "渝", "冀", "晋", "蒙", "辽", "吉", "黑", "苏", "浙", "京", "闽", "赣", "鲁", "豫", "鄂", "湘", "粤", "桂", "琼", "川", "贵", "云", "藏", "陕", "甘", "青", "宁", "新", "警", "学", "O"]
alphabets = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'O']
ads = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'O']

def make_label(img_dir, save_gt_folder, phase):
    crop_img_save_dir = os.path.join(save_gt_folder, phase, 'crop_imgs')
    os.makedirs(crop_img_save_dir, exist_ok=True)

    f_det = open(os.path.join(save_gt_folder, phase, 'det.txt'), 'w', encoding='utf-8')
    f_rec = open(os.path.join(save_gt_folder, phase, 'rec.txt'), 'w', encoding='utf-8')

    i = 0
    for filename in tqdm(os.listdir(os.path.join(img_dir, phase))):
        str_list = filename.split('-')
        if len(str_list) < 5:
            continue
        coord_list = str_list[3].split('_')
        txt_list = str_list[4].split('_')
        boxes = []
        for coord in coord_list:
            boxes.append([int(x) for x in coord.split("&")])
        boxes = [boxes[2], boxes[3], boxes[0], boxes[1]]
        lp_number = provinces[int(txt_list[0])] + alphabets[int(txt_list[1])] + ''.join([ads[int(x)] for x in txt_list[2:]])

        # det
        det_info = [{'points':boxes, 'transcription':lp_number}]
        f_det.write('{}\t{}\n'.format(os.path.join(phase, filename), json.dumps(det_info, ensure_ascii=False)))

        # rec
        boxes = np.float32(boxes)
        img = cv2.imread(os.path.join(img_dir, phase, filename))
        # crop_img = img[int(boxes[:,1].min()):int(boxes[:,1].max()),int(boxes[:,0].min()):int(boxes[:,0].max())]
        crop_img = get_rotate_crop_image(img, boxes)
        crop_img_save_filename = '{}_{}.jpg'.format(i,'_'.join(txt_list))
        crop_img_save_path = os.path.join(crop_img_save_dir, crop_img_save_filename)
        cv2.imwrite(crop_img_save_path, crop_img)
        f_rec.write('{}/crop_imgs/{}\t{}\n'.format(phase, crop_img_save_filename, lp_number))
        i+=1
    f_det.close()
    f_rec.close()

def get_rotate_crop_image(img, points):
    '''
    img_height, img_width = img.shape[0:2]
    left = int(np.min(points[:, 0]))
    right = int(np.max(points[:, 0]))
    top = int(np.min(points[:, 1]))
    bottom = int(np.max(points[:, 1]))
    img_crop = img[top:bottom, left:right, :].copy()
    points[:, 0] = points[:, 0] - left
    points[:, 1] = points[:, 1] - top
    '''
    assert len(points) == 4, "shape of points must be 4*2"
    img_crop_width = int(
        max(
            np.linalg.norm(points[0] - points[1]),
            np.linalg.norm(points[2] - points[3])))
    img_crop_height = int(
        max(
            np.linalg.norm(points[0] - points[3]),
            np.linalg.norm(points[1] - points[2])))
    pts_std = np.float32([[0, 0], [img_crop_width, 0],
                          [img_crop_width, img_crop_height],
                          [0, img_crop_height]])
    M = cv2.getPerspectiveTransform(points, pts_std)
    dst_img = cv2.warpPerspective(
        img,
        M, (img_crop_width, img_crop_height),
        borderMode=cv2.BORDER_REPLICATE,
        flags=cv2.INTER_CUBIC)
    dst_img_height, dst_img_width = dst_img.shape[0:2]
    if dst_img_height * 1.0 / dst_img_width >= 1.5:
        dst_img = np.rot90(dst_img)
    return dst_img

img_dir = r'D:\code\OpenCv\completed\dataset\images'
save_gt_folder = r'D:\code\OpenCv\completed\dataset\images\PPOCR'
# phase = 'train' # change to val and test to make val dataset and test dataset
for phase in ['train','test']:
    make_label(img_dir, save_gt_folder, phase)