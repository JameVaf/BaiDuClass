#ifndef __SORTTESTHELPER_HPP__
#define __SORTTESTHELPER_HPP__
#include<iostream>
#include<ctime>
#include<cassert>
#include<functional>
#include<string>


namespace SortHeaper
{
    // 默认按小排序的函数指针
    template <typename T>
    std::function<bool(T, T)> less = [](T L, T R) -> bool
    {
        if (L <= R)
        {
            return true;
        }
        return false;
    };

    // 按大排序的函数指针
    template <typename T>
    std::function<bool(T, T)> greater = [](T L, T R) -> bool
    {
        if (R <= L)
        {
            return true;
        }
        return false;
    };

    //比较的函数指针
    template <typename T>
    using compareFuncPtr = std::function<bool(T L, T R)>;

    // 排序算法函数指针
    template <typename T>
    using sortFuncPtr = std::function<void(T *arr, int n, compareFuncPtr<T> compare )>;



    //产生n个 int 类型的数据
    int *generateRangeArray(int n, int RangeL, int RangeR)
    {

        assert(RangeL <= RangeR);
        int *arr = new int[n];
        srand((unsigned int)time(NULL));
        for (int i = 0; i < n;++i)
        {
            arr[i] = rand()%(RangeR - RangeL + 1) + RangeL;
        }
        return arr;
    };

    //打印数据元素
    template<typename T>
    void printf(T *arr,int n)
    {
        for (int i = 0; i < n;++i)
            std::cout << arr[i] << " ";
        std::cout << std::endl;
    };

    //判断元素按序排列是否成功
    template <typename T>
    bool isSorted(T arr[],int n,compareFuncPtr<T> compare = less<T>)
    {
        for (int i = 0, j = i + 1; i < n;++i,++j)
        {
            if(!compare(arr[i],arr[j]))
            {
                return false;
            }
        }
        return true;
    };

    //得到排序算法的耗时
    template <typename T>
    void testSortTime(const std::string sortName,sortFuncPtr<T> sort,T arr[],int n,compareFuncPtr<T> compare )
    {
        clock_t startTime = clock();
        sort(arr, n,compare);
        clock_t endTime = clock();

        assert(isSorted(arr, n,compare));
        std::cout << sortName << " : " << double(endTime - startTime) / CLOCKS_PER_SEC << " s " << std::endl;
    };
};

#endif //__SORTTESTHELPER_HPP__