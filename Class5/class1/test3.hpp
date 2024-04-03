/**
 * 选择排序算法 对学生结构体进行比较
 *
 */

#include<iostream>

template<typename T>
bool less(T L, T R)
{
    if( L < R)
    {
        return true;
    }
    return false;
}

template<typename T>
void selecttionSort(T arr[], int n,bool (*compare)(T L,T R) = less)
{
    for (int i = 0; i < n; ++i)
    {
        int minNumber = i; // 假设第i个元素最小
        for (int j = i + 1; j < n; ++j)
        {
            if (compare(arr[j],arr[minNumber]))
            {
                minNumber = j;
            }
        }
        std::swap(arr[i], arr[minNumber]);
    }
}