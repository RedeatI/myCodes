import keyboard
import pyautogui
import time
import threading

# 标志位，用于控制连点器的启动和停止
clicking = False
button = 'left'  # 默认左键

# 连点器函数
def clicker(button):
    while clicking:
        pyautogui.click(button=button)
        time.sleep(0.01)  # 调整点击间隔时间

# 启动连点器
def start_clicking(button_type):
    global clicking, button
    clicking = True
    button = button_type
    threading.Thread(target=clicker, args=(button,)).start()

# 停止连点器
def stop_clicking():
    global clicking
    clicking = False

# 绑定按键
keyboard.add_hotkey('F7', lambda: start_clicking('left'))
keyboard.add_hotkey('F8', lambda: start_clicking('right'))
keyboard.add_hotkey('F9', stop_clicking)

print("按下 F7 键开始左键连点，按下 F8 键开始右键连点，按下 F9 键停止连点。")

# 保持脚本运行
keyboard.wait('esc')