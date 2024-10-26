import os
import cv2
from ultralytics import YOLO

def calculate_iou(box1, box2):
    """计算两个边界框的交并比（IoU）"""
    x1, y1, x2, y2 = box1
    x1_, y1_, x2_, y2_ = box2

    xi1 = max(x1, x1_)
    yi1 = max(y1, y1_)
    xi2 = min(x2, x2_)
    yi2 = min(y2, y2_)
    inter_area = max(0, xi2 - xi1) * max(0, yi2 - yi1)

    box1_area = (x2 - x1) * (y2 - y1)
    box2_area = (x2_ - x1_) * (y2_ - y1_)
    union_area = box1_area + box2_area - inter_area

    iou = inter_area / union_area
    return iou

# 加载模型
model_path = "D:\\_code\\myCodes\\pyCodes\\CarCheck\\models"
model = YOLO(os.path.join(model_path, "yolov8n.pt"))

# 输入输出路径
input_folder = "D:\\_code\\myCodes\\pyCodes\\CarCheck\\pics"
output_folder = "D:\\_code\\myCodes\\pyCodes\\CarCheck\\temp"
os.makedirs(output_folder, exist_ok=True)

# 记录没有检测到车辆的文件
no_vehicle_files = []

# 遍历输入文件夹中的所有图片
for filename in os.listdir(input_folder):
    if filename.endswith(".jpg"):
        img_path = os.path.join(input_folder, filename)
        img = cv2.imread(img_path)
        
        # 进行车辆检测，最多尝试10次
        for attempt in range(10):
            results = model(img)
            
            # 确保 results 是一个列表，并且每个元素都有 boxes 属性
            if isinstance(results, list) and hasattr(results[0], 'boxes'):
                base_name = filename.split("pic_")[1].split(".")[0]
                vehicle_count = 0
                vehicle_boxes = []
                
                for i, (box, cls) in enumerate(zip(results[0].boxes.xyxy, results[0].boxes.cls)):  # 使用xyxy格式
                    if int(cls) in [2, 5, 7]:  # 类别为2表示车辆，5表示公共汽车，7表示卡车
                        box_tuple = tuple(map(int, box[:4]))
                        # 检查是否与已有的检测框重叠
                        if not any(calculate_iou(box_tuple, existing_box) > 0.5 for existing_box in vehicle_boxes):
                            vehicle_boxes.append(box_tuple)
                            vehicle_count += 1
                
                if vehicle_count > 0:
                    for i, box in enumerate(vehicle_boxes):
                        x1, y1, x2, y2 = box  # 提取坐标
                        cropped_img = img[y1:y2, x1:x2]
                        if vehicle_count == 1:
                            output_filename = f"{base_name}.jpg"
                        else:
                            output_filename = f"{base_name}-{i+1}.jpg"
                        cv2.imwrite(os.path.join(output_folder, output_filename), cropped_img)
                        print(f"Saved cropped image: {output_filename}")
                    break  # 如果检测到车辆，则跳出尝试循环
                else:
                    print(f"No vehicles detected in attempt {attempt + 1} for image: {filename}")
            else:
                print(f"No boxes found in attempt {attempt + 1} for image: {filename}")
        
        if vehicle_count == 0:
            print(f"Failed to detect any vehicles in image: {filename} after 2 attempts")
            no_vehicle_files.append(filename)

# 输出没有检测到车辆的文件
if no_vehicle_files:
    print("The following files did not detect any vehicles:")
    for file in no_vehicle_files:
        print(file)
else:
    print("All files detected vehicles successfully.")