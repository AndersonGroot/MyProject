#pragma once

template<typename TYPE>
class CMyStack
{
public:
    //�ڵ㣨��������
	struct StackNode
	{
        StackNode(const TYPE& elem = 0)
		{
			elem_ = elem;
			next_ = nullptr;
		}

		TYPE elem_;       //Ԫ��
		StackNode *next_; //��һ�ڵ�
	};
public:
	CMyStack();
	~CMyStack();
	//��ȡ�ڵ����
	int GetSize() const;
	//�ж�ջ�Ƿ�Ϊ��
	bool IsEmpty();
	//��ջ
	void push(const TYPE &elem);
	//��ջ
	void pop();
	//��ȡջ��
	TYPE &top();

private:
	StackNode *head_;  //ͷ�ڵ�
	unsigned int size_;//���нڵ����
};

template<typename TYPE>
CMyStack<TYPE>::CMyStack()
{
	head_ = nullptr;
	size_ = 0;
}

template<typename TYPE>
CMyStack<TYPE>::~CMyStack()
{
    while (!IsEmpty())
    {
        pop();
    }
}

template<typename TYPE>
int CMyStack<TYPE>::GetSize() const
{
	return size_;
}

template<typename TYPE>
bool CMyStack<TYPE>::IsEmpty()
{
	return size_ == 0;
}

template<typename TYPE>
void CMyStack<TYPE>::push(const TYPE &elem)
{
	StackNode *node = new StackNode(elem);
	node->next_ = head_;
	head_ = node;
	size_++;
}

template<typename TYPE>
void CMyStack<TYPE>::pop()
{
	if (IsEmpty())
	{
		throw "Stack is empty";
	}

	StackNode *oldHead = head_;
	head_ = head_->next_;
	delete oldHead;
	size_--;
}

template<typename TYPE>
TYPE& CMyStack<TYPE>::top()
{
	if (IsEmpty())
	{
		throw"Stack is empty";
	}

	return head_->elem_;
}