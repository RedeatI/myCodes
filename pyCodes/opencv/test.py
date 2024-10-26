import os
import shutil
from tqdm import tqdm

# 定义源目录和目标目录
source_dir = r'D:\code\OpenCv\completed\dataset\images\val'
train_dir = r'D:\code\OpenCv\completed\dataset\images\train'
test_dir = r'D:\code\OpenCv\completed\dataset\images\test'

# 创建目标目录
os.makedirs(train_dir, exist_ok=True)
os.makedirs(test_dir, exist_ok=True)

# 获取源目录中的所有文件
files = [f for f in os.listdir(source_dir) if f.endswith('.jpg')]

# 按8:2比例分配文件
split_index = int(0.8 * len(files))
train_files = files[:split_index]
test_files = files[split_index:]

# 移动文件的函数
def move_files(file_list, source_dir, target_dir, desc):
    for file in tqdm(file_list, desc=desc):
        source_file = os.path.join(source_dir, file)
        target_file = os.path.join(target_dir, file)
        try:
            shutil.move(source_file, target_file)
        except PermissionError as e:
            print(f"文件: {file}")
            print(f"权限错误: {e}")
        except Exception as e:
            print(f"文件: {file}")
            print(f"错误: {e}")

# 移动文件
move_files(train_files, source_dir, train_dir, "移动到训练集")
move_files(test_files, source_dir, test_dir, "移动到测试集")

print("文件已成功分配到训练集和测试集。")