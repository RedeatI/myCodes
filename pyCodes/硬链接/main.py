import os

def create_hard_links(input_dir, output_dir):
    # 检查输出文件夹是否存在，如果不存在则创建它
    if not os.path.exists(output_dir):
        os.makedirs(output_dir)
    
    # 遍历输入文件夹中的所有文件和子文件夹
    for root, dirs, files in os.walk(input_dir):
        # 计算相对路径
        relative_path = os.path.relpath(root, input_dir)
        # 在输出文件夹中创建相应的子文件夹
        output_subdir = os.path.join(output_dir, relative_path)
        if not os.path.exists(output_subdir):
            os.makedirs(output_subdir)
        
        for file in files:
            input_file_path = os.path.join(root, file)
            output_file_path = os.path.join(output_subdir, file)
            
            try:
                # 创建硬链接
                os.link(input_file_path, output_file_path)
                print(f"硬链接创建成功: {output_file_path}")
            except Exception as e:
                print(f"创建硬链接失败: {output_file_path}, 错误: {e}")

# 示例用法
input_dir = input("请输入输入文件夹地址: ")
output_dir = input("请输入输出文件夹地址: ")
create_hard_links(input_dir, output_dir)