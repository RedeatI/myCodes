#include <iostream>

void mySwap(int *&a, int *&b, int *&c)
{
    int *atemp = &(*a);
    a = b;
    b = c;
    c = atemp;
}

void work()
{
    int a, b, c;
    std::cout << "Please input three numbers: \n";
    std::cin >> a >> b >> c;
    int *aPtr = &a, *bPtr = &b, *cPtr = &c;

    mySwap(aPtr, bPtr, cPtr);
    std::cout << "After swap: " << *aPtr << " " << *bPtr << " " << *cPtr << std::endl;
}

int main()
{
    work();

    return 0;
}