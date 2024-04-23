#ifndef __MYSTACK_HPP__
#define __MYSTACK_HPP__

template<class _Type>
class myStakc
{
private:


    class Node
    {
    public:
        _Type* data_;
        Node *next_;
        Node()
        {
            data_ = nullptr;
            next_ = nullptr;
        }
        Node(const _Type& elem )
        {
            data_ = new _Type(elem);
            if(data_ == nullptr)
            {
                std::cerr << "new _Type Failed" << std::endl;
            }
            next_ = nullptr;
        }
        ~Node()
        {
            delete data_;
            data_ = nullptr;
        }
    };
    Node *header_;
    Node *back_;
    size_t size_;

public:
    myStakc()
    {
        header_ = new Node;
        back_ = nullptr;
        header_->next_ = back_;
        size_ = 0;
    }
    ~myStakc()
    {
        Node *curr = header_;
        while(curr !=nullptr )
        {
            Node *temp = curr->next_;
            delete curr;
            curr = temp;
        }
    }

    bool Empty()
    {
        if(size_ == 0)
        {
            return true;
        }
        return false;
    }

    _Type top()
    {
        if(size_ == 0)
        {
            throw std::runtime_error("top empty stack");
        }
        return *(back_->data_);
    }
    
    bool push_back(const _Type& elem)
    {
        if(size_ == 0)
        {
            Node *temp = new Node(elem);
            header_->next_ = temp;
            back_ = temp;
            back_->next_ = nullptr;
            size_++;
            return true;
        }
        Node *temp = new Node(elem);
        back_->next_ = temp;
        back_ = temp;
        back_->next_ = nullptr;
        size_++;
        return true;
    }

    _Type pop_back()
    {
        _Type ret;
        if (size_ == 0)
        {
            throw std::runtime_error("top empty stack");
        }
        //找到倒数第二的数据
        if(size_ == 1)
        {
            ret= *back_->data_;
            delete back_;
            back_ = nullptr;
            header_->next_ = nullptr;
            size_--;
            return ret;
        }
        Node *curr = header_->next_;
        for (int i = 0; i < size_ - 2;i++)
        {
            curr = curr->next_;
        }
        ret = *(back_->data_);
        delete back_;
        back_ = curr;
        back_->next_ = nullptr;
        --size_;
        return ret;
    }

    size_t size()
    {
        return size_;
    }

};
#endif //__MYSTACK_HPP__