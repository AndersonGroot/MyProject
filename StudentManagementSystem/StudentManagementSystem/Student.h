#pragma once
#include "MyString.h"

//ѧ����
class CStudent
{
public:
    CStudent(unsigned int id = 1, 
             CMyString name = " ", 
             unsigned int year = 0,
             unsigned int month = 0,
             char sex = '/0', 
             bool IsExist = true, 
             unsigned int offset = 0);
    CStudent(const CStudent& obj);
    ~CStudent();
public:
    bool IsExist_;       //״̬
    unsigned int offset_;//�ļ���ƫ����
    unsigned int Length_;//��������
    unsigned int id_;    //id
    CMyString name_;     //����
    unsigned int year_;  //��
    unsigned int month_; //��
    char sex_;           //�Ա�
};

