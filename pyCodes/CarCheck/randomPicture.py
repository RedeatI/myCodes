import os
import shutil
import random

# 设置路径
images_path = 'D:/code/OpenCv/completed/dataset/CCPD2019/ccpd_weather'
dst_image_path_a = 'D:/code/OpenCv/completed/dataset/images'

# 打印路径以检查是否正确
print(f"images_path: {images_path}")

# 检查目录是否存在
if not os.path.exists(images_path):
    print(f"目录不存在: {images_path}")
else:
    print(f"目录存在: {images_path}")

# 列出目录中的所有文件
all_files = os.listdir(images_path)

# 获取所有图像文件（包括 .jpg 和 .png）
all_images = [f for f in all_files if f.endswith('.jpg') or f.endswith('.png')]

# 检查是否找到了图像文件
if not all_images:
    print("未找到任何图像文件")
else:
    print(f"找到 {len(all_images)} 个图像文件")

# 随机打乱图像文件
random.shuffle(all_images)

# 分割训练、验证和测试集（例如 70% 训练，20% 验证，10% 测试）
train_split = int(0.7 * len(all_images))
val_split = int(0.9 * len(all_images))
train_images = all_images[:train_split]
val_images = all_images[train_split:val_split]
test_images = all_images[val_split:]

# 移动图像文件到相应目录
for image in train_images:
    src_image_path = os.path.join(images_path, image)
    dst_image_path = os.path.join(dst_image_path_a, 'train', image)

    # 检查文件是否存在
    if os.path.exists(src_image_path):
        shutil.move(src_image_path, dst_image_path)

for image in val_images:
    src_image_path = os.path.join(images_path, image)
    dst_image_path = os.path.join(dst_image_path_a, 'val', image)

    # 检查文件是否存在
    if os.path.exists(src_image_path):
        shutil.move(src_image_path, dst_image_path)

for image in test_images:
    src_image_path = os.path.join(images_path, image)
    dst_image_path = os.path.join(dst_image_path_a, 'test', image)

    # 检查文件是否存在
    if os.path.exists(src_image_path):
        shutil.move(src_image_path, dst_image_path)