#include "stdafx.h"
#include "MyString.h"
#include <string.h>

CMyString::CMyString()
{
	//���ó�ʼ��
	init();
}

CMyString::CMyString(char* p)
{
	//��ʼ����ֵ
	init();
	initString(p);
}

CMyString::CMyString(CMyString& obj)
{
	init();
	initString(obj.getBuff());
}

CMyString::~CMyString()
{
	if (IsEmpty())
	{
		return;
	}

	if (getBuff() != nullptr)
	{
		delete[] getBuff();
		setBuff(nullptr);
		setIsEmpty(true);
	}
}

/*
�����ַ���ָ��
����һ���ַ���ָ��
�޷���ֵ
*/
void CMyString::setBuff(char* p)
{
	pBuff_ = p;
}

/*
�����ַ���ʵ�ʳ���
����һ��ʵ�ʳ���
�޷���ֵ
*/
void CMyString::setLength(unsigned int len)
{
	len_ = len;
}

/*
�����ַ�����󳤶�
����һ����󳤶�
�޷���ֵ
*/
void CMyString::setLimit(unsigned int limit)
{
	limit_ = limit;
}

/*
�����Ƿ�Ϊ���ַ���
����һ������
�޷���ֵ
*/
void CMyString::setIsEmpty(bool IsEmpty)
{
	IsEmpty_ = IsEmpty;
}

/*
��ȡ�ַ���ָ��
�޲���
����ֵ���ַ���ָ��
*/
char* CMyString::getBuff() const
{
	return pBuff_;
}

/*
��ȡ�ַ���ʵ�ʳ���
�޲���
����ֵ���ַ���ʵ�ʳ���
*/
int CMyString::getLength() const
{
	return len_;
}

/*
��ȡ�ַ�����󳤶�
*/
int CMyString::getLimit() const
{
	return limit_;
}

/*
��ȡ�ַ���״̬
�޲���
����ֵ������
*/
bool CMyString::IsEmpty() const
{
	return IsEmpty_;
}

/*
����ռ�
����һ���ռ��С
�޷���ֵ
*/
void CMyString::allocBuff(int len)
{
	char *pBuff = new char[len];
	if (pBuff == nullptr)
	{
		throw "CMyString::allocBuff error";
	}

	setBuff(pBuff);
    setLimit(len - 1);
}

/*
��ʼ��
�޲���
�޷���ֵ
*/
void CMyString::init()
{
	setBuff(nullptr);
	setLength(0);
	setLimit(0);
	setIsEmpty(true);
}

/*
�䳤�ַ�����ֵ
����һ���ַ���ָ��
�޷���ֵ
*/
void CMyString::initString(char* p)
{
	int len = strlen(p);

	//����ǿյ�
	if (IsEmpty())
	{
		allocBuff(len + 1);
		setLength(len);
		setIsEmpty(false);
		strcpy(pBuff_, p);
	}
	//���ǿյ�
	else
	{
		//���ԭ�ռ䲻��
		if (getLimit() < len)
		{
			if (getBuff() != nullptr)
			{
				delete[] getBuff();   //���ͷ�ԭ�ռ�
				setBuff(nullptr);
			}   
			allocBuff(len + 1);//������ռ�
			setLength(len);
			strcpy(pBuff_, p);
		}
		else
		{
			strcpy(pBuff_, p);
			setLength(len);
		}
	}
}

/*
������������ıȽ�
����һ������������
*/
int CMyString::Compare(const CMyString &obj)
{
	return strcmp(getBuff(), obj.getBuff());
}

/*
���������=��֧���ַ�����ֵ�������
����һ���ַ���ָ��
*/
CMyString& CMyString::operator= (char *p)
{
	initString(p);
	return *this;
}

/*
���������=��֧�������ֵ�������
����һ������������
*/
CMyString& CMyString::operator= (const CMyString &obj)
{
	initString(obj.getBuff());
	return *this;
}

/*
���ز����<< ,֧�ֶ�����ֱ������ַ���
����һ������������
*/
ostream& operator<< (ostream &os, CMyString &obj)
{
	os << obj.getBuff();
	return os;
}

