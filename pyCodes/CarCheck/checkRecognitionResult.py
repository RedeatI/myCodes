import pandas as pd
import ast

# 读取CSV文件
df = pd.read_csv("recognition_results.csv")

# 解析字符串形式的列表为数值列表
def parse_confidence(confidence_str):
    try:
        return ast.literal_eval(confidence_str)
    except (ValueError, SyntaxError):
        return []

# 计算每个列表的平均值
df["Confidence"] = df["Confidence"].apply(parse_confidence)
df["Average Confidence"] = df["Confidence"].apply(lambda x: sum(x) / len(x) if x else 0)

# 计算平均Confidence
average_confidence = df["Average Confidence"].mean()

# 计算正确率
correct_predictions = df["Correct"].sum()
total_predictions = len(df)
accuracy = correct_predictions / total_predictions if total_predictions > 0 else 0

# 计算平均计算时间
average_processing_time = df["Processing Time (s)"].mean()

# 打印结果，精确到小数点后六位
print(f"Average Confidence: {average_confidence:.6f}")
print(f"Accuracy: {accuracy:.6f}")
print(f"Average Processing Time: {average_processing_time:.6f} seconds")