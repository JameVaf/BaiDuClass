#include<iostream>
#include "MyVector.hpp"

int main()
{
    Algorithm::vector<int> v;
    v.push_back(10);
    std::cout << v.size() << std::endl;

    return 0;
}