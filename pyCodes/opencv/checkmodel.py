#coding:utf-8
from ultralytics import YOLO
import cv2

# 所需加载的模型目录
path = 'D:/code/OpenCv/completed/train/weights/best.pt'
# 需要检测的视频地址
video_path = "D:/code/OpenCv/Videos/carcode.mp4"

# 加载预训练模型
model = YOLO(path, task='detect')

# 打开视频文件
cap = cv2.VideoCapture(video_path)

# 检查视频是否成功打开
if not cap.isOpened():
    print("Error: Could not open video.")
    exit()

# 获取视频的宽度和高度
frame_width = int(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
frame_height = int(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))

while cap.isOpened():
    ret, frame = cap.read()
    if not ret:
        break

    # 检测当前帧
    results = model(frame)
    res = results[0].plot()

    # 显示检测结果
    cv2.imshow("YOLOv8 Detection", res)

    # 按 'q' 键退出
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# 释放视频捕获和写入对象
cap.release()
cv2.destroyAllWindows()