#pragma once
#include "MyString.h"

//学生类
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
    bool IsExist_;       //状态
    unsigned int offset_;//文件中偏移量
    unsigned int Length_;//姓名长度
    unsigned int id_;    //id
    CMyString name_;     //姓名
    unsigned int year_;  //年
    unsigned int month_; //月
    char sex_;           //性别
};

