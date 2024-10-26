import os
import cv2
from tqdm import tqdm

def convert_yolo_to_opencv(yolo_label, img_width, img_height):
    with open(yolo_label, 'r') as file:
        lines = file.readlines()
    
    opencv_labels = []
    for line in lines:
        parts = line.strip().split()
        x_center = float(parts[1]) * img_width
        y_center = float(parts[2]) * img_height
        width = float(parts[3]) * img_width
        height = float(parts[4]) * img_height
        x = int(x_center - width / 2)
        y = int(y_center - height / 2)
        opencv_labels.append((x, y, int(width), int(height)))
    
    return opencv_labels

def create_samples_file(images_dir, labels_dir, output_file):
    image_files = [f for f in os.listdir(images_dir) if f.endswith('.jpg')]
    
    with open(output_file, 'w') as file:
        for image_name in tqdm(image_files, desc="Processing images"):
            image_path = os.path.join(images_dir, image_name)
            label_path = os.path.join(labels_dir, image_name.replace('.jpg', '.txt'))
            
            img = cv2.imread(image_path)
            img_height, img_width = img.shape[:2]
            
            opencv_labels = convert_yolo_to_opencv(label_path, img_width, img_height)
            for label in opencv_labels:
                file.write(f"{image_path} 1 {label[0]} {label[1]} {label[2]} {label[3]}\n")

images_dir = 'D:/code/OpenCv/completed/dataset/images/train'
labels_dir = 'D:/code/OpenCv/completed/dataset/labels/train'
output_file = 'positives.txt'
create_samples_file(images_dir, labels_dir, output_file)