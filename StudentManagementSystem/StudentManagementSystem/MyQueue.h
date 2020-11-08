#pragma once

template<typename TYPE>
class CMyQueue
{
    //节点（单向链表）
    struct QueueNode
    {
        QueueNode(const TYPE& elem = 0)
        {
            elem_ = elem;
            next_ = nullptr;
        }

        TYPE elem_;      //元素
        QueueNode *next_; //下一节点
    };
public:
	CMyQueue();
	~CMyQueue();
    //获取节点个数
	int getSize() const;
    //判断队列是否为空
    bool IsEmpty();
    //入队列
    void push(const TYPE& elem);
    //出队列
    void pop();
    //获取队列头部
    TYPE& getTop() const;
private:
    QueueNode *head_;   //头节点
    QueueNode *tail_;   //尾节点
    unsigned int size_; //队列节点个数
};

template<typename TYPE>
CMyQueue<TYPE>::CMyQueue()
{
    head_ = tail_ = nullptr;
    size_ = 0;
}

template<typename TYPE>
CMyQueue<TYPE>::~CMyQueue()
{
    while (!IsEmpty())
    {
        pop();
    }
}

template<typename TYPE>
int CMyQueue<TYPE>::getSize() const
{
    return size_;
}

template<typename TYPE>
bool CMyQueue<TYPE>::IsEmpty()
{
    return size_ == 0;
}

template<typename TYPE>
void CMyQueue<TYPE>::push(const TYPE& elem)
{
    QueueNode *node = new QueueNode(elem);

    if (IsEmpty())
    {
        head_ = tail_ = node;
    }
    else
    {
        tail_->next_ = node;
        tail_ = node;
    }

    size_++;
}

template<typename TYPE>
void CMyQueue<TYPE>::pop()
{
    if (IsEmpty())
    {
        throw "Queue is empty";
    }

    QueueNode *oldHead = head_;
    head_ = head_->next_;
    delete oldHead;

    size_--;
}

template<typename TYPE>
TYPE& CMyQueue<TYPE>::getTop() const
{
    if (IsEmpty())
    {
        throw "Queue is empty";
    }
    return head_->elem_;
}