/**
 * 选择排序算法
 * 
*/

void selecttionSort(int arr[],int n)
{
    for (int i = 0; i < n;++i)
    {
        int minNumber = i;  //假设第i个元素最小
        for (int j = i +1; j < n;++j)
        {
            if(arr[j] < arr[minNumber])
            {
                minNumber = j;
            }

        }
        //std::swap();
        int temp = arr[i];
        arr[i] = arr[minNumber];
        arr[minNumber] = temp;
    }
}