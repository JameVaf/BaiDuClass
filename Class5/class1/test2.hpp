/**
 * 选择排序算法模版实现
 *
 */

template<typename _T>
void selecttionSort(_T arr[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        int minNumber = i; // 假设第i个元素最小
        for (int j = i + 1; j < n; ++j)
        {
            if (arr[j] < arr[minNumber])
            {
                minNumber = j;
            }
        }
        std::swap(arr[i],arr[minNumber]);

    }
}