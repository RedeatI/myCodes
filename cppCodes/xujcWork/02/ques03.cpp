#include <iostream>

void transform(int* matrix, int row, int col)
{
    for (int j = 0; j < col; j++)
    {
        for (int i = 0; i < row; i++)
        {
            std::cout << matrix[i * col + j] << " ";
        }
        std::cout << std::endl;
    }
}

void work()
{
    int* matrix = new int[3 * 4];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix[i * 4 + j] = i * 4 + j + 1;
        }
    }

    transform(matrix, 3, 4);
}

int main()
{
    work();

    return 0;
}