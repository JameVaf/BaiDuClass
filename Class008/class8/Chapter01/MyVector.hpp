#ifndef __MYVECTOR_HPP__
#define __MYVECTOR_HPP__
#include<iostream>
#include<algorithm>
#include<memory>
#include<string.h>
namespace Algorithm
{
    //迭代器,只是使用,并不管理内存
    template<class _Type>
    class Iterator
    {
    public:
        
        Iterator() = delete;
        Iterator(const Iterator &other)
        {
            this->data_ = other.data_;
        }
        Iterator(const Iterator&& other)
        {
            this->data_ = other.data_;
        }
        Iterator& operator =(const Iterator& other)
        {
            this->data_ = other->data_;
        }
        Iterator &operator=(const Iterator &&other)
        {
            this->data_ = other->data_;
        }

       //对解引用重载
        template <class _T>
        friend _T &operator*(const Iterator<_T> &other);

        //对->重载
        _Type* operator->()
        {
            return data_;
        }
    private:
        _Type *data_;
    };



    

    template<typename _Type>
    class vector
    {
    public:
        vector()
        {
            length_ = 0;
            capacity_ = 10;
            data_ = (_Type*)malloc(capacity_ * sizeof(_Type));
            //清空内存的无效内容
            memset(data_, 0, (capacity_ * sizeof(_Type)));
        }
        vector(size_t n,_Type elem)
        {
            length_ = 0;
            capacity_ = n;
            data_ = (_Type)malloc(capacity_ * sizeof(_Type));
            for (int i = 0; i <n;++i)
            {
                data_[i] = elem;
            }
   
        }
        bool push_back(_Type elem)
        {
            //首先判断容量是否足够
            if(capacity_ == length_)
            {
                //容量不够,扩容两倍
                
                _Type* new_data = (_Type *)malloc(capacity_*2  * sizeof(_Type));
                //清空无效内容
                memset(new_data, 0, (capacity_ * 2 * sizeof(_Type)));
                memcpy(new_data, data_, (capacity_ * sizeof(_Type)));
                free(data_);
                data_ = new_data;
                capacity_ *= 2;
                //迭代器更新

            }
            data_[length_] = elem;
            ++length_;
            return true; 
        }
        _Type push_pop()
        {
            _Type temp = data_[length_-1];
            memset(data_ + (length_ - 1), 0, sizeof(_Type));
            --length_;
            return temp;
        }
        size_t size() const
        {
            return length_;
        }
        size_t capacity() const
        {
            return capacity_;
        }
        bool empty() const
        {
            return length_ ?false: true;
        }
        bool resize(size_t n)
        {
            if(n <= capacity_)
            {
                std::cout << "resize capacity < origin capacity" << std::endl;
                return false;
            }
            _Type new_data = (_Type *)malloc(n);
            // 清空无效内容
            memset(new_data, 0, n);
            memcpy(new_data, data_, (capacity_ * sizeof(_Type)));
            free(data_);
            data_ = new_data;
            capacity_  = n;

        }
        

    private:
        _Type *data_;    //保存数据
        size_t length_; //保存元素个数
        size_t capacity_;   //空间的大小

    };



    // 对解引用重载
    template <class _T>
    _T&operator*(const Iterator<_T> &other)
    {
        return *(other.data_);
    }
};

#endif //__MYVECTOR_HPP__