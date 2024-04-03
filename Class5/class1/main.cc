#include<iostream>

#include "test3.hpp"
#include "SortTestHelper.hpp"
using namespace SortHeaper;

struct Student
{
    std::string name;
    int score;   //分数
    bool operator<(const Student& other)
    {
        if(this->score < other.score)
        {
            return true;
        }
        if(this->score == other.score)
        {
            return this->name < other.name ? true : false;
        }
        return false;
    }

    friend std::ostream& operator <<(std::ostream &os,const Student& t)
    {
        os << "Student Name:" << t.name << "  score:" << t.score;
        return os;
    }
};

int main()
{

    // Student arr[] = {{"Jame", 123}, {"Device", 321}, {"Simple", 0}, {"Fallen", 4}};
    // int n = sizeof(arr) / sizeof(Student);
    // for (int i = 0; i < n;++i)
    // {
    //     std::cout << arr[i] << " ";
    // }
    // std::cout << std::endl;

    // //selecttionSort<Student>(arr, n);
    // selecttionSort<Student>(arr, n, [](Student l,Student r) -> bool{
    //     if(r < l)
    //     {
    //         return true;
    //     }
    //     return false;
    // });
    // for (int i = 0; i < n; ++i)
    // {
    //     std::cout << arr[i] << " ";
    // }
    // std::cout << std::endl;

    int n = 150;
    int *arr = SortHeaper::generateRangeArray(n, 1, 1000);
    SortHeaper::printf(arr, n);
    selecttionSort(arr, n);
    SortHeaper::printf(arr, n);
    bool is= isSorted(arr, n);
    std::cout << "是否排序成功:"<<is << std::endl;
    //SortHeaper::testSortTime("select ",selecttionSort,arr,n);

   // SortHeaper::testSortTime<int>("select Sort", selecttionSort<int>, arr, n);

    delete[] arr;
    return 0;
}



