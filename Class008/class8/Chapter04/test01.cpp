#include <iostream>
#include <vector>

std::vector<int> Test(std::vector<int> &input)
{
    auto isZero = input.rbegin();
    auto notZero = input.rbegin();
    while (isZero != input.rend() && notZero != input.rend())
    {
        // 首先找0和非0的位置
        while (*isZero != 0 && isZero != input.rend())
        {
            ++isZero;
        }
        while (*notZero == 0 && notZero != input.rend())
        {
            ++notZero;
        }
        auto temp = *isZero;
        *isZero = *notZero;
        *notZero = temp;
    }

    return input;
};

int main()
{
    std::vector<int> v{1, 0, 0, 68, 0, 5, 60, 0, 0, 6, 0, 4, 0};
    for (auto iter : v)
    {
        std::cout << iter << " ";
    }
    std::cout << std::endl;
    Test(v);
    for (auto iter : v)
    {
        std::cout << iter << " ";
    }
    std::cout << std::endl;

    return 0;
}