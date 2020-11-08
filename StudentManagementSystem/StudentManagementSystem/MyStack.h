#pragma once

template<typename TYPE>
class CMyStack
{
public:
    //节点（单向链表）
	struct StackNode
	{
        StackNode(const TYPE& elem = 0)
		{
			elem_ = elem;
			next_ = nullptr;
		}

		TYPE elem_;       //元素
		StackNode *next_; //下一节点
	};
public:
	CMyStack();
	~CMyStack();
	//获取节点个数
	int GetSize() const;
	//判断栈是否为空
	bool IsEmpty();
	//入栈
	void push(const TYPE &elem);
	//出栈
	void pop();
	//获取栈顶
	TYPE &top();

private:
	StackNode *head_;  //头节点
	unsigned int size_;//队列节点个数
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