import torch
from ultralytics import YOLO

def main():
    # 加载 YOLOv8 模型
    model = YOLO('yolov8n.pt')  # 你可以根据需要选择不同的预训练模型

    # 检查并使用 GPU
    device = 'cuda' if torch.cuda.is_available() else 'cpu'
    model.to(device)

    # 训练模型
    try:
        model.train(data='D:/code/OpenCv/completed/dataset/dataset.yaml', epochs=10, batch=32, device=device)
    except ValueError as e:
        print(f"训练模型时发生错误: {e}")

    # 导出模型为 ONNX 格式到指定路径
    model.export(format='onnx', save_dir='D:/code/OpenCv/completed')

    print("模型已导出至 D:/code/OpenCv/completed")

if __name__ == '__main__':
    main()