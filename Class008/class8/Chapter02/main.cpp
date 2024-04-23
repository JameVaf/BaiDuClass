#include<iostream>
#include "MyStack.hpp"

int main()
{
    myStakc<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    std::cout << v.top() << std::endl;
    v.pop_back();
    std::cout << v.top() << std::endl;
    return 0;
}