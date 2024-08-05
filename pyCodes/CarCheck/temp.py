import torch
from torch.utils.data import DataLoader, TensorDataset

# 假设你已经定义了模型和数据集
# 这里使用简单的示例数据集和模型
dataset = TensorDataset(torch.randn(1000, 3, 224, 224), torch.randint(0, 10, (1000,)))
model = torch.nn.Sequential(
    torch.nn.Conv2d(3, 16, kernel_size=3, stride=1, padding=1),
    torch.nn.ReLU(),
    torch.nn.Flatten(),
    torch.nn.Linear(16 * 224 * 224, 10)
).cuda()

def find_max_batch_size(model, dataset, initial_batch_size=1, max_memory_usage=0.9):
    batch_size = initial_batch_size
    while True:
        try:
            # 尝试加载数据并进行一次前向传播
            data_loader = DataLoader(dataset, batch_size=batch_size)
            for data in data_loader:
                inputs, labels = data
                inputs, labels = inputs.cuda(), labels.cuda()
                outputs = model(inputs)
                break
            # 检查显存使用情况
            memory_allocated = torch.cuda.memory_allocated()
            memory_reserved = torch.cuda.memory_reserved()
            print(f"Batch size: {batch_size}, Memory allocated: {memory_allocated}, Memory reserved: {memory_reserved}")
            if memory_allocated / memory_reserved > max_memory_usage:
                print(f"Stopping: Memory usage exceeded {max_memory_usage * 100}%")
                break
            batch_size *= 2
        except RuntimeError as e:
            if 'out of memory' in str(e):
                print(f"Out of memory error at batch size: {batch_size}")
                break
            else:
                raise e
    return batch_size // 2

# 示例用法
max_batch_size = find_max_batch_size(model, dataset)
print(f"最大批次大小: {max_batch_size}")