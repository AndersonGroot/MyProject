#include "stdafx.h"
#include "MyString.h"
#include <string.h>

CMyString::CMyString()
{
	//调用初始化
	init();
}

CMyString::CMyString(char* p)
{
	//初始化后赋值
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
设置字符串指针
参数一：字符串指针
无返回值
*/
void CMyString::setBuff(char* p)
{
	pBuff_ = p;
}

/*
设置字符串实际长度
参数一：实际长度
无返回值
*/
void CMyString::setLength(unsigned int len)
{
	len_ = len;
}

/*
设置字符串最大长度
参数一：最大长度
无返回值
*/
void CMyString::setLimit(unsigned int limit)
{
	limit_ = limit;
}

/*
设置是否为空字符串
参数一：真或假
无返回值
*/
void CMyString::setIsEmpty(bool IsEmpty)
{
	IsEmpty_ = IsEmpty;
}

/*
获取字符串指针
无参数
返回值：字符串指针
*/
char* CMyString::getBuff() const
{
	return pBuff_;
}

/*
获取字符串实际长度
无参数
返回值：字符串实际长度
*/
int CMyString::getLength() const
{
	return len_;
}

/*
获取字符串最大长度
*/
int CMyString::getLimit() const
{
	return limit_;
}

/*
获取字符串状态
无参数
返回值：真或假
*/
bool CMyString::IsEmpty() const
{
	return IsEmpty_;
}

/*
申请空间
参数一：空间大小
无返回值
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
初始化
无参数
无返回值
*/
void CMyString::init()
{
	setBuff(nullptr);
	setLength(0);
	setLimit(0);
	setIsEmpty(true);
}

/*
变长字符串赋值
参数一：字符串指针
无返回值
*/
void CMyString::initString(char* p)
{
	int len = strlen(p);

	//如果是空的
	if (IsEmpty())
	{
		allocBuff(len + 1);
		setLength(len);
		setIsEmpty(false);
		strcpy(pBuff_, p);
	}
	//不是空的
	else
	{
		//如果原空间不够
		if (getLimit() < len)
		{
			if (getBuff() != nullptr)
			{
				delete[] getBuff();   //先释放原空间
				setBuff(nullptr);
			}   
			allocBuff(len + 1);//再申请空间
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
类对象与类对象的比较
参数一：类对象的引用
*/
int CMyString::Compare(const CMyString &obj)
{
	return strcmp(getBuff(), obj.getBuff());
}

/*
重载运算符=，支持字符串赋值给类对象
参数一：字符串指针
*/
CMyString& CMyString::operator= (char *p)
{
	initString(p);
	return *this;
}

/*
重载运算符=，支持类对象赋值给类对象
参数一：类对象的引用
*/
CMyString& CMyString::operator= (const CMyString &obj)
{
	initString(obj.getBuff());
	return *this;
}

/*
重载插入符<< ,支持对象名直接输出字符串
参数一，类对象的引用
*/
ostream& operator<< (ostream &os, CMyString &obj)
{
	os << obj.getBuff();
	return os;
}

