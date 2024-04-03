#ifndef __LIST_H__
#define __LIST_H__
#include<iostream>
#include<algorithm>

namespace MyAlgorithm
{
    template<typename T>
    struct Node
    {
        Node(T temp) {
            data_ = temp;
            next_ = nullptr;
        };
        T data_;
        Node *next_;
    };

    template<typename T>
    class List
    {
    public:
        List() : head(nullptr),length_(0){};
        List(T val):length_(1)  {head = new Node<T>(val);};

        //尾插法
        List& insert(T val){ 
            if(nullptr == head_)
            {
                
                head_ = new Node<T>(val);
                ++length_;
            }else{
                Node *temp = head;
                while(nullptr != temp->next)
                {
                    temp = temp->next;
                }
                temp->next = new Node<T>(val);
                ++length_
            }
        };

        //得到链表长度
        int length() { return length_; }

        //对链表排序,返回false 说明是对空链表排序,返回true说明排序成功
        //采用冒泡排序
        bool sort()
        {
            Node *prex, *temp, next;
            prex = temp = next = nullptr;
            //空的链表
            if(nullptr == head_ )
            {
                return false;
            }

            prex = head;

            //只有一个元素的链表
            if(nullptr ==prex->next_)
            {
                return true;
            }
            temp = prex->next_;
            next = temp->next_;//其有可能为nullptr

            
            // for (int count = length_; count >= 2;--count)
            // {
            //     Node *second_prex, *second_temp, *second_next;
            //     second_prex = prex;
            //     second_temp = temp;
            //     second_next = next;
            //     while(nullptr != second_next )
            //     {
            //         if(second_temp->data_ > second_next)
            //         {
            //             second_temp->next_ = second_next->next_;
            //             second_next->next_ = second_temp;
            //             second_prex->next_ = second_next;
            //         }
            //         second_prex = second_temp;
            //         second_temp = second_next;
            //         second_next = second_next->next_;
            //     }
            //     prex = temp;
            //     temp = next;
            //     next = next->next_;
            // }
            return ture;
        }


        //打印链表
        void printf()
        {
            if(nullptr == head_)
            {
                std::cout << "null List" << std::endl;
            }
            Node *temp = head_;
            while(nullptr != temp)
            {
                std::cout << temp->data_ << " ";
                temp = temp->next_;
            }
        }
    private:
        Node *head_ = nullptr;
        int length_ = 0; // 记录长度
    };
}

#endif //__LIST_H__