import os

import datetime

from PIL import Image

from PIL.ExifTags import TAGS

dir_path = r"D:\photos"

# 获取文件列表

file_list = os.listdir(dir_path)

for file_name in file_list:

    file_path = os.path.join(dir_path, file_name)

    try:

        # 尝试打开图片文件

        with Image.open(file_path) as img:

            # 获取图片的EXIF信息

            exif_data = img._getexif()

            # 如果图片包含EXIF信息

            if exif_data:

                # 获取拍摄日期和时间信息

                datetime_str = exif_data.get(36867)

                if datetime_str:

                    # 将字符串解析为datetime对象

                    dt = datetime.datetime.strptime(datetime_str, "%Y:%m:%d %H:%M:%S")

                    # 将修改日期设置为拍摄日期

                    os.utime(file_path, (os.path.getatime(file_path), dt.timestamp()))

    except Exception as e:

        print(f"{file_name}: 处理出错，错误信息：{e}")