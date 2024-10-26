import os

# 负样本图像目录
negatives_dir = 'D:/code/OpenCv/completed/dataset/images/val'

# 输出文件
output_file = 'negatives.txt'

# 获取负样本图像文件列表
negatives = [f for f in os.listdir(negatives_dir) if os.path.isfile(os.path.join(negatives_dir, f))]

# 写入描述文件
with open(output_file, 'w') as f:
    for neg in negatives:
        f.write(os.path.join(negatives_dir, neg) + '\n')

print(f'Created {output_file} with {len(negatives)} negative samples.')