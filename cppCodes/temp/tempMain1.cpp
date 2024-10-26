#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

// 计算阶乘的函数
long double factorial(int n)
{
	if (n == 0 || n == 1)
		return 1.0; // 0! 和 1! 都是 1
	long double result = 1.0;
	for (int i = 2; i <= n; ++i)
	{
		result *= i; // 计算 n! 的值
	}
	return result;
}

// 使用 Ramanujan 公式计算 pi 的函数
long double calculatePi(int iterations)
{
	long double pi = 0.0;
	long double sqrt8 = std::sqrt(8.0); // 计算 sqrt(8)
	long double factor = 9801.0;		// Ramanujan 公式中的常数

	for (int k = 0; k < iterations; ++k)
	{
		// 计算公式中的分子
		long double num = factorial(4 * k) * (1103 + 26390 * k);
		// 计算公式中的分母
		long double denom = std::pow(factorial(k), 4) * std::pow(396, 4 * k);
		// 计算当前项的值
		long double term = num / denom;
		pi += term; // 将当前项累加到 pi 中

		// 如果当前项非常小，提前终止循环
		if (term < std::numeric_limits<long double>::epsilon())
		{
			break;
		}
	}

	// 计算最终的 pi 值
	pi = (sqrt8 / factor) * pi;
	pi = 1.0 / pi; // 取倒数得到最终的 pi 值
	return pi;
}

int main()
{
	int precision;
	std::cin >> precision; // 从标准输入读取精度

	int iterations = 10;					  // 设定迭代次数
	long double pi = calculatePi(iterations); // 计算 pi 的值

	// 根据输入的精度输出 pi 的值
	for (int i = 0; i < precision; ++i)
	{
		std::cout << std::fixed << std::setprecision(11 + i) << pi << std::endl;
	}
	return 0;
}