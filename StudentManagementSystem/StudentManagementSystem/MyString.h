#pragma once
#include <iostream>
using namespace std;

//�䳤�ַ���
class CMyString
{
public:
	CMyString();
	CMyString(char* p);
	CMyString(CMyString& obj);
	~CMyString();
	//��ȡ�ַ���
	char* getBuff() const; 
	//��ȡ�ַ���ʵ�ʳ���
	int getLength() const; 
	//��ȡ�ַ�����󳤶�
	int getLimit() const;  
	//�ж��Ƿ���ַ���
	bool IsEmpty() const;  
	//������������ıȽ�
	int Compare(const CMyString &obj);
	//����=
	CMyString& operator= (char *p);
	//����
	CMyString& operator= (const CMyString &obj);
	//����<<�������֧�ֶ�����ֱ�����
	friend ostream& operator<< (ostream &os, CMyString &obj);
	
private:
	//����ռ�
	void allocBuff(int len);
	//��ʼ��
	void init();            
	//�䳤�ַ�����ֵ
	void initString(char* p);
	void setBuff(char* p);   
	//����ʵ�ʳ���
	void setLength(unsigned int len);
	//�����ַ�����󳤶�
	void setLimit(unsigned int limit);
	//�����Ƿ���ַ���
	void setIsEmpty(bool IsEmoty);  
private:
	char *pBuff_;        //�ַ���
	bool IsEmpty_;       //�Ƿ�Ϊ��
	unsigned int len_;   //�ַ���ʵ�ʳ���
	unsigned int limit_; //�ַ�����󳤶�
};


