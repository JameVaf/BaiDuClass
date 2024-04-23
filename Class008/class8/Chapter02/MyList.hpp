#include<iostream>

template<class _Type>
class List
{
private:
    class Node
    {
    public:
    Node(_Type elem)
    {
        try
        {
            data_ = new _Type(elem);
            next_ = nullptr;
        }
        catch(const std::bad_alloc& e)
        {
            std::cerr << "Memery alloc Failed" << e.what() << std::endl;
        }
        throw;
    }
    ~Node()
    {
        delete data_;
        data_ = nullptr;
    }
        _Type *data_;
        Node *next_;
    }

private: 
    Node *header_;  //头指针
    Node *end_;//尾指针指向尾部元素,方便进行尾插操作
    size_t length_; //List的长度
    

public:
    //构造函数
    List()
    {
        header = nullptr;
        end_ = nullptr;
        length_ = 0;
    }
    ~List()
    {
        Node *curr = header->next;
        while(curr != nullptr)
        {
            Node *nextNode = curr->next;
            free(curr);
            curr = nextNode;
        }
    }
    bool empty()
    {
        return length_ ? false : true;
    }
    bool push_back(_Type elem)
    {
        //首先产生元素
        Node *temp = new Node(elem);
        end_->next_ = temp;
        end_ = temp;
        ++length_;
    }
    bool pop_back()
    {
        //如果只有一个元素,直接删除
         
        //首先根据长度找到倒数第二个元素
        for (int i = 0,Node* curr = header_; i < length_;++i)
        {
            curr = header->next_;
        }
    }

    

};