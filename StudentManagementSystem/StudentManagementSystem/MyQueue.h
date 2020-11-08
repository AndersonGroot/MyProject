#pragma once

template<typename TYPE>
class CMyQueue
{
    //�ڵ㣨��������
    struct QueueNode
    {
        QueueNode(const TYPE& elem = 0)
        {
            elem_ = elem;
            next_ = nullptr;
        }

        TYPE elem_;      //Ԫ��
        QueueNode *next_; //��һ�ڵ�
    };
public:
	CMyQueue();
	~CMyQueue();
    //��ȡ�ڵ����
	int getSize() const;
    //�ж϶����Ƿ�Ϊ��
    bool IsEmpty();
    //�����
    void push(const TYPE& elem);
    //������
    void pop();
    //��ȡ����ͷ��
    TYPE& getTop() const;
private:
    QueueNode *head_;   //ͷ�ڵ�
    QueueNode *tail_;   //β�ڵ�
    unsigned int size_; //���нڵ����
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