#include <iostream>

double a = 600;
double b = 350;

double aDiscount = 0.75;
double bDiscount = 0.8;

double getAPrice()
{
    return a * aDiscount;
}

double getBPrice()
{
    return b * bDiscount;
}

double difference()
{
    return abs(getAPrice() - getBPrice());
}

double getTotalPrice()
{
    return getAPrice() + getBPrice();
}

double* price()
{
    double* res = new double[4];
    res[0] = getAPrice();
    res[1] = getBPrice();
    res[2] = difference();
    res[3] = getTotalPrice();

    return res;
}

void work()
{
    double* myPrices = price();

    std::cout << "A price: " << myPrices[0] << std::endl;
    std::cout << "B price: " << myPrices[1] << std::endl;
    std::cout << "Difference: " << myPrices[2] << std::endl;
    std::cout << "Total price: " << myPrices[3] << std::endl;
}

int main()
{
    work();

    return 0;
}