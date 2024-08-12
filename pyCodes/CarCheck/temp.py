import shutil
import os

# 定义要删除的文件夹路径
folder_path = r'D:\code\OpenCv\completed\dataset\images\PPOCR\val\crop_imgs'

# 检查文件夹是否存在
if os.path.exists(folder_path):
    # 删除文件夹及其所有内容
    shutil.rmtree(folder_path)
    print(f"文件夹 {folder_path} 已成功删除。")
else:
    print(f"文件夹 {folder_path} 不存在。")