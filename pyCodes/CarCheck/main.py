import os
import cv2
import sys
from PIL import ImageFont
import hyperlpr3 as lpr3
import time
import pandas as pd

# 解析车牌号
provinces = ["皖", "沪", "津", "渝", "冀", "晋", "蒙", "辽", "吉", "黑", "苏", "浙", "京", "闽", "赣", "鲁", "豫", "鄂", "湘", "粤", "桂", "琼", "川", "贵", "云", "藏", "陕", "甘", "青", "宁", "新", "警", "学", "O"]
alphabets = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'O']
ads = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'O']

# 解析文件名以提取车牌信息
def parse_filename(filename):
    # 去掉文件扩展名
    filename = filename.split('.')[0]
    
    # 分割字段
    fields = filename.split('-')
    
    # 解析字段
    area = float(fields[0])
    tilt_degree = tuple(map(int, fields[1].split('_')))
    bounding_box = tuple(map(int, fields[2].replace('&', '_').split('_')))
    vertices = tuple(map(int, fields[3].replace('&', '_').split('_')))
    lp_indices = list(map(int, fields[4].split('_')))
    brightness = int(fields[5])
    blurriness = int(fields[6])

    # 检查车牌索引长度是否有效
    if len(lp_indices) < 7:
        return None
   
    # 生成车牌号
    lp_number = provinces[lp_indices[0]] + alphabets[lp_indices[1]] + ''.join([ads[i] for i in lp_indices[2:]])

    return {
        'area': area,
        'tilt_degree': tilt_degree,
        'bounding_box': bounding_box,
        'vertices': vertices,
        'lp_number': lp_number,
        'brightness': brightness,
        'blurriness': blurriness
    }

# 检查识别的车牌是否正确
def is_correct_plate(recognized_plates, correct_plate):
    for recognized_plate in recognized_plates:
        if recognized_plate == correct_plate:
            return True
    return False

# 中文字体加载
font_ch = ImageFont.truetype(r"D:\_code\myCodes\pyCodes\CarCheck\platech.ttf", 20, 0)

# 数据集路径
dataset_path = "D:/code/OpenCv/completed/dataset/images/test"

# 图像处理器类
class ImageProcessor:
    def __init__(self, dataset_path, catcher : lpr3.LicensePlateCatcher):
        self.dataset_path = dataset_path
        self.catcher = catcher
        self.total_images = 0
        self.correct_predictions = 0
        self.total_processing_time = 0
        self.avg_processing_time = 0
        self.accuracy = 0
        self.process_speed = 0

    # 处理单张图片
    def process_image(self, image_file):
        image_path = os.path.join(self.dataset_path, image_file)
        
        # 读取图片
        image = cv2.imread(image_path)
        
        # 记录开始时间
        start_time = time.time()

        # 执行识别算法
        results = self.catcher(image)
        recognized_plates = [result[0] for result in results]

        # 记录结束时间
        end_time = time.time()

        # 计算处理时间
        processing_time = end_time - start_time

        # 解析文件名以获取正确的车牌号
        parse = parse_filename(image_file)
        if parse is None:
            return

        # 更新处理的图片数量和总处理时间
        self.total_images += 1
        self.total_processing_time += processing_time

        # 如果没有识别到车牌，直接返回
        if not recognized_plates:
            return

        correct_plate = parse['lp_number']
        # 如果识别的车牌正确，增加正确识别计数
        if is_correct_plate(recognized_plates, correct_plate):
            self.correct_predictions += 1
        
def processModel(processor):
    # 遍历数据集中的图片文件
    for image_file in os.listdir(dataset_path):
        if processor.total_images >= 100:
            break
        
        processor.process_image(image_file)
        # 计算平均处理时间、准确率和处理速度
        processor.avg_processing_time = f"{processor.total_processing_time / processor.total_images:.4f}"
        processor.accuracy = f"{100.0 * processor.correct_predictions / processor.total_images:.4f}%"
        processor.process_speed = f"{processor.total_images / processor.total_processing_time:.4f}"

        # 清除当前行并输出新的统计数据
        sys.stdout.write("\r")
        sys.stdout.write(f"Processed images: {processor.total_images} | ")
        sys.stdout.write(f"Average processing time: {processor.avg_processing_time}s | ")
        sys.stdout.write(f"Accuracy: {processor.accuracy} | ")
        sys.stdout.write(f"Process speed: {processor.process_speed} FPS")
        sys.stdout.flush()
    
    # 输出换行
    print()

def originModel(detect_level):
# 输出检测级别和会话提供者
    print(f"Detect level: {detect_level}")

    # 初始化车牌识别器
    catcher = lpr3.LicensePlateCatcher(detect_level=detect_level)
    
    # 初始化图像处理器
    processor = ImageProcessor(dataset_path, catcher)
    
    # 处理图片
    processModel(processor)

    # 写入统计数据
    df.loc[len(df)] = [
        'Detect_level=' + str(detect_level), 
        processor.total_images,
        processor.avg_processing_time,
        processor.accuracy,
        processor.process_speed
    ]

    # 释放资源
    del catcher
    del processor

# 主函数
def main():
    # 低检测级别
    detect_level = lpr3.DETECT_LEVEL_LOW
    #originModel(detect_level, 'CUDAExecutionProvider')# : unsupport now
    originModel(detect_level)

    # 高检测级别
    detect_level = lpr3.DETECT_LEVEL_HIGH
    #originModel(detect_level, 'CUDAExecutionProvider')# : unsupport now
    originModel(detect_level)
    

# 创建一个 DataFrame 来存储统计数据
df = pd.DataFrame(columns=['Modification', 'Processed Images', 'Average Processing Time (s)', 'Accuracy (%)', 'Process Speed (FPS)'])

main()

# 保存统计数据
df.to_csv("results_improve.csv", index=False)

# 输出统计数据
print(df)

# 输出数据保存位置
print("Results saved to results_improve.csv")

# 释放资源
del df