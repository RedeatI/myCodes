import os
import cv2
import numpy as np
import pandas as pd
from PIL import ImageFont, Image, ImageDraw
import hyperlpr3 as lpr3
from scipy.__config__ import show
from tqdm import tqdm
import time

def draw_plate_on_image(img, box, text, font):
    img = np.copy(img)  # 创建图像的可写副本
    x1, y1, x2, y2 = box
    cv2.rectangle(img, (x1, y1), (x2, y2), (139, 139, 102), 2, cv2.LINE_AA)
    cv2.rectangle(img, (x1, y1 - 20), (x2, y1), (139, 139, 102), -1)
    data = Image.fromarray(img)
    draw = ImageDraw.Draw(data)
    draw.text((x1 + 1, y1 - 18), text, (255, 255, 255), font=font)
    res = np.asarray(data)
    return res

# 中文字体加载
font_ch = ImageFont.truetype("platech.ttf", 20, 0)

# 实例化识别对象
catcher = lpr3.LicensePlateCatcher(detect_level=lpr3.DETECT_LEVEL_HIGH)

# 数据集路径
dataset_path = "D:/codeForVsCode/CarCheck/pics"

# 初始化统计变量
total_images = 0
correct_predictions = 0

# 初始化结果列表
results_list = []

# 遍历数据集
image_files = [f for f in os.listdir(dataset_path) if f.endswith(".jpg")]
total_images = len(image_files)

for image_file in image_files:
    image_path = os.path.join(dataset_path, image_file)
    
    # 读取图片
    image = cv2.imread(image_path)
    
    # 记录开始时间
    start_time = time.time()
    
    # 执行识别算法
    results = catcher(image)
    recognized_plates = []
    confidences = []
    boxes = []
    for code, conf, type_idx, box in results:
        recognized_plates.append(code)
        confidences.append(conf)
        boxes.append(box)
    
    # 记录结束时间
    end_time = time.time()
    
    # 计算处理时间
    processing_time = end_time - start_time

    # 显示目前处理的图片
    print(f"Processing image: {image_file}")

    # 依据用户输入判断是否正确
    is_correct = None
    if recognized_plates:
        for i, (plate, conf, box) in enumerate(zip(recognized_plates, confidences, boxes)):
            print(f"Recognized plate {i+1}: {plate} - Confidence: {conf:.2f}")
            # 绘制车牌区域
            image_with_box = draw_plate_on_image(image, box, f"{plate} - {conf:.2f}", font_ch)
            cv2.imshow(f"License Plate {i+1}", image_with_box)
            user_input = input("Is the plate correct? (y/n): ").lower()
            if user_input == "y":
                is_correct = True
                correct_predictions += 1
            else:
                is_correct = False
            cv2.destroyWindow(f"License Plate {i+1}")
    
    # 添加结果到列表
    results_list.append({
        "File Name": image_file,
        "Recognized Plate": recognized_plates,
        "Confidence": confidences if recognized_plates else None,
        "Correct": is_correct,
        "Processing Time (s)": processing_time
    })

    # 关闭所有窗口
    cv2.destroyAllWindows()

# 计算准确性
accuracy = correct_predictions / total_images if total_images > 0 else 0
print(f"Total images: {total_images}")
print(f"Correct predictions: {correct_predictions}")
print(f"Accuracy: {accuracy:.2f}")

# 创建数据表
results_df = pd.DataFrame(results_list)
print(results_df)

# 保存数据表到文件
results_df.to_csv("recognition_results.csv", index=False)

# 关闭所有OpenCV窗口
cv2.destroyAllWindows()