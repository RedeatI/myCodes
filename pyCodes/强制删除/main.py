import shutil
import os
import stat
import psutil

def kill_processes_using_file(file_path):
    for proc in psutil.process_iter(['pid', 'name']):
        try:
            for item in proc.open_files():
                if item.path == file_path:
                    proc.terminate()
                    proc.wait()
        except (psutil.NoSuchProcess, psutil.AccessDenied, psutil.ZombieProcess):
            pass

def on_rm_error(func, path, exc_info):
    # 修改文件或文件夹的权限
    os.chmod(path, stat.S_IWRITE)
    try:
        func(path)
    except Exception as e:
        print(f"删除路径 {path} 时发生错误: {e}")

def delete_path(path):
    # 检查路径是否存在
    if os.path.exists(path):
        try:
            # 如果是文件夹，删除文件夹及其所有内容
            if os.path.isdir(path):
                # 对文件夹中的每个文件解除访问
                for root, dirs, files in os.walk(path):
                    for file in files:
                        file_path = os.path.join(root, file)
                        kill_processes_using_file(file_path)
                        os.chmod(file_path, stat.S_IWRITE)
                shutil.rmtree(path, onexcr=on_rm_error)
                print(f"文件夹 {path} 已成功删除。")
            # 如果是文件，删除文件
            elif os.path.isfile(path):
                # 强制解除文件的访问
                kill_processes_using_file(path)
                os.chmod(path, stat.S_IWRITE)
                os.remove(path)
                print(f"文件 {path} 已成功删除。")
        except Exception as e:
            print(f"删除路径 {path} 时发生错误: {e}")
    else:
        print(f"路径 {path} 不存在。")

if __name__ == "__main__":
    # 输入路径
    path = input("请输入要删除的文件或文件夹路径: ")
    delete_path(path)