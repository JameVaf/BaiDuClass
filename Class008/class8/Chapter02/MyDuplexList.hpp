#ifndef __MYDUOLEXLIST_HPP__
#define __MYDUOLEXLIST_HPP__

#include<iostream>

namespace MyAlgorithm
{
    template<class _Type>
    class MyDuplexList
    {
    private:
        class Node
        {
        public:
            _Type *data_;
            Node *prex_;
            Node *next_;
            Node(_Type data)
            {
                data_ = nullptr;
                data_ = new _Type(data);
                if(nullptr == data_)
                {
                    std::cerr << "new data Failed" << std::endl;
                }
                prex_ = nullptr;
                next_ = nullptr;
            }
            ~Node()
            {
                if(nullptr != data_)
                {
                    delete data_;
                }
                data_ = nullptr;
            }
            Node& operator = (Node<_Type> &&other)
            {
                this->data_ = other->data_;
                this->prex_ = other->prex_;
                this->next_ = other->next_;

                other->data_ = nullptr;
                other->prex_ = nullptr;
                other->next = nullptr;
            }
        }



        int size_; // 链表元素的个数
        Node *head_; // 头部指针
        Node *back_;              // 尾部指针

        // 无参构造
        MyDuplexList()
        {
            head_ = nullptr;
            back_ = nullptr;
            size_ = 0;
        }

        //有参构造
        MyDuplexList(const _Type elem)
        {
            Node *temp = new Node(elem);
            if(nullptr == temp)
            {
                std::cerr << "MyDuplexList(_Type elem) Failed" << std::endl;
                std::throw;
            }
            head_ = temp;
            back_ = temp;
            ++size_;
        }

        //构造n个elem
        MyDuplexList(int n,const _Type elem)
        {
            for (int i = 0; i < n;++i)
            {
              bool i =  push_back(elem);
              if(!i)
              {
                std::cerr << "MyDuplexList(int n,const _Type elem) Failed" << std::endl;
              }
            }
        }

        //初始化列表构造
        MyDuplexList(const initializer_list<_Type> & lt)
        {
            for(auto iter:lt)
            {
               bool i = push_back(iter);
               if (!i)
               {
                   std::cerr << "MyDuplexList(const initializer_list<_Type> & lt) Failed" << std::endl;
               }
            }
        }

        //
        MyDuplexList(MyDuplexList<_Type>& other)
        {
            //首先挨个取得元素
            Node *othercurr = other.head_;
  
            while(othercurr != nullptr)
            {
                bool i = push_back(*(othercurr->data_));
                if (!i)
                {
                    std::cerr << " MyDuplexList(MyDuplexList<_Type>& other) Failed" << std::endl;
                }
            }
            
        }

        MyDuplexList(MyDuplexList<_Type> &&other)
        {
    
        }

        MyDuplexList& operator=(MyDuplexList<_Type> &other)
        {

        }

        MyDuplexList &operator=(MyDuplexList<_Type> &&other)
        {

        }

        //尾部插入元素
        bool push_back(const _Type &elem)
        {

        }

        //头部插入元素
        bool push_front(const _Type &elem)
        {

        }

        //尾部删除元素
        _Type pop_back(void)
        {

        }

        //删除头部元素
        _Type pop_fornt(void)
        {

        }

        //中间插入元素
        bool insert(int index,_Type elem)
        {

        }

        //判断元素是否为空
        bool empty()
        {

        }

        //删除某个元素(可能有多个)
        bool erase(_Type elem)
        {

        }

        //删除指定索引的元素
        bool erase(int index,_Type elem)
        {

        }

        //清除容器
        bool clear(void)
        {

        }

        //交换容器
        friend bool myswap(MyDuplexList<_Type> &a, MyDuplexList<_Type> &b);

        //operator []
        _Type oeprator [](int index)
        {

        }

        //返回头结点元素
        _Type fornt(void)
        {

        }

        //返回尾部节点
        _Type back(void)
        {

        }

        
    };








    template<class _Type>
    bool myswap(MyDuplexList<_Type> &a,MyDuplexList<_Type> &b)
    {

    }
}

#endif //__MYDUOLEXLIST_HPP__