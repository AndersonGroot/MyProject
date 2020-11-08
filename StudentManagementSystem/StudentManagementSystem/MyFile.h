#pragma once
#include "Student.h"
#include "MyAVLTree.h"

//文件类
class CMyFile
{
public:
    CMyFile();
    ~CMyFile();
    //写入数据
    void Write(CStudent &obj);
    //读取数据
    void Read();
    //修改文件数据
    void ModifyState(CStudent &obj);
public:
    //ID树
    CMyAVLTree<CStudent> TreeID_;
    //姓名树
    CMyAVLTree<CStudent> TreeName_;
};

//按ID比较大小
int compareID(CStudent& obj1, CStudent& obj2);
//按姓名比较大小
int compareName(CStudent& obj1, CStudent& obj2);
