#pragma once
#include <iostream>
using namespace std;

//变长字符串
class CMyString
{
public:
	CMyString();
	CMyString(char* p);
	CMyString(CMyString& obj);
	~CMyString();
	//获取字符串
	char* getBuff() const; 
	//获取字符串实际长度
	int getLength() const; 
	//获取字符串最大长度
	int getLimit() const;  
	//判断是否空字符串
	bool IsEmpty() const;  
	//类对象与类对象的比较
	int Compare(const CMyString &obj);
	//重载=
	CMyString& operator= (char *p);
	//重载
	CMyString& operator= (const CMyString &obj);
	//重载<<插入符，支持对象名直接输出
	friend ostream& operator<< (ostream &os, CMyString &obj);
	
private:
	//申请空间
	void allocBuff(int len);
	//初始化
	void init();            
	//变长字符串赋值
	void initString(char* p);
	void setBuff(char* p);   
	//设置实际长度
	void setLength(unsigned int len);
	//设置字符串最大长度
	void setLimit(unsigned int limit);
	//设置是否空字符串
	void setIsEmpty(bool IsEmoty);  
private:
	char *pBuff_;        //字符串
	bool IsEmpty_;       //是否为空
	unsigned int len_;   //字符串实际长度
	unsigned int limit_; //字符串最大长度
};


