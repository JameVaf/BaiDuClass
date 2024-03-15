#ifndef MYLIST_HPP
#define MyLIST_HPP
class MyList;
class  Node
{
public:
    friend MyList;
    Node(int index) : index_(index), prex_(nullptr), next_(nullptr){};
    Node() = delete;
    Node(const Node &) = delete;
    Node(const Node &&) = delete;
    Node &operator=(const Node &) = delete;
    Node &operator=(const Node &&) = delete;

private:
    ~Node()//使Node对象只能在堆上
    {
        
    }
    

private:
    int index_;     //现在的内存页序号
    Node* prex_;  //上一个节点
    Node* next_;  //下一个节点
};
using NodePtr = Node *;

class MyList
{
public:

    MyList(int copacity = 10) : copacity_(copacity), headNode_(nullptr), size_(0)
    {
        headNode_->prex_ = nullptr;
        headNode_->next_ = nullptr;
    };
    MyList() = delete;
    MyList(const MyList &) = delete;
    MyList(const MyList &&) = delete;
    MyList &operator=(const MyList &) = delete;
    MyList &operator=(const MyList &&) = delete;

    bool push_back(int node)
    {
        if(nullptr == headNode_)
        {
            headNode_ = new Node(node);
            headNode_->prex_ = headNode_;
            headNode_->next_ = headNode_;
            return true;
        }
        if(size_ == copacity_)//
        {
            return false;
        }
        NodePtr temp = headNode_->prex_;
        

    }

private:
    NodePtr headNode_;//链表的头节点
    int size_;   //链表的元素个数
    int copacity_;//链表的容量
};

#endif //MYLIST_HPP