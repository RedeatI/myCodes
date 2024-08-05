import os
import yaml

def main():
    device = 'cuda'  # 或者 'cpu'，根据你的实际情况

    # 检查 dataset.yaml 文件是否存在并且内容正确
    dataset_path = 'D:/code/OpenCv/completed/dataset/dataset.yaml'
    try:
        with open(dataset_path, 'r') as file:
            dataset = yaml.safe_load(file)
            if not dataset:
                raise ValueError("dataset.yaml 文件内容为空或格式不正确")
    except FileNotFoundError:
        print(f"文件未找到: {dataset_path}")
        return
    except yaml.YAMLError as e:
        print(f"解析 YAML 文件时发生错误: {e}")
        return

    # 检查图像和标签文件是否存在
    train_images_path = dataset['train']
    train_labels_path = train_images_path.replace('images', 'labels')
    if not os.path.exists(train_images_path):
        print(f"训练图像目录不存在: {train_images_path}")
        return
    if not os.path.exists(train_labels_path):
        print(f"训练标签目录不存在: {train_labels_path}")
        return

if __name__ == '__main__':
    main()