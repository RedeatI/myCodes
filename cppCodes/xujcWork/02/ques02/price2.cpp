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

void price(double &APrice, double &BPrice, double &diff, double &totalPrice)
{
    APrice = getAPrice();
    BPrice = getBPrice();
    diff = difference();
    totalPrice = getTotalPrice();
}

void work()
{
    double APrice, BPrice, diff, totalPrice;

    price(APrice, BPrice, diff, totalPrice);
    
    std::cout << "A price: " << APrice << std::endl;
    std::cout << "B price: " << BPrice << std::endl;
    std::cout << "Difference: " << diff << std::endl;
    std::cout << "Total price: " << totalPrice << std::endl;
}

int main()
{
    work();

    return 0;
}