#include "stdafx.h"
#include "MyFile.h"
#include "Student.h"
#include <stdio.h>

CMyFile::CMyFile()
{
    TreeID_.pfnCompare_ = compareID;
    TreeName_.pfnCompare_ = compareName;
}


CMyFile::~CMyFile()
{
}

/*
写入数据到文件中
参数一：引用的学生类
无返回值
*/
void CMyFile::Write(CStudent &obj)
{
    //尾部添加方式打开数据文件
    FILE *fp = fopen("..//MyData.bin", "ab+");
    if (fp == nullptr)
    {
        throw "CMyFile::Write() error:fopen";
    }
    obj.Length_ = obj.name_.getLimit() + 1;
    //获取偏移量
    fseek(fp, 0, SEEK_END);
    obj.offset_ = ftell(fp);
    //写入学生信息
    fwrite(&obj.IsExist_, sizeof(bool), 1, fp);
    fwrite(&obj.offset_, sizeof(int), 1, fp);
    fwrite(&obj.Length_, sizeof(int), 1, fp);
    fwrite(&obj.id_, sizeof(int), 1, fp);
    fwrite(obj.name_.getBuff(), obj.Length_, 1, fp);
    fwrite(&obj.year_, sizeof(int), 1, fp);
    fwrite(&obj.month_, sizeof(int), 1, fp);
    fwrite(&obj.sex_, sizeof(char), 1, fp);
    fclose(fp);
}

/*
从文件中读取数据
无参数
无返回值
*/
void CMyFile::Read()
{
    CStudent obj;
    //二进制读写方式打开文件
    FILE *fp = fopen("..//MyData.bin", "rb+");
    if (fp == nullptr)
    {
        throw "CMyFile::Read() error:fopen";
    }
    char szBuff[1024] = { 0 }; //申请一个缓存区
    //获取文件尾
    fseek(fp, 0, SEEK_END);
    unsigned int nEnd = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    while (true)
    {
        fread(&obj.IsExist_, sizeof(bool), 1, fp);
        fread(&obj.offset_, sizeof(int), 1, fp);
        fread(&obj.Length_, sizeof(int), 1, fp);
        fread(&obj.id_, sizeof(int), 1, fp);
        //读取姓名到缓存区
        fread(szBuff, obj.Length_, 1, fp);
        //将缓存区的内容给CMyString的对象，避免析构时的释放问题
        obj.name_ = szBuff;
        //fread(obj.name_.getBuff(), obj.Length_, 1, fp);
        fread(&obj.year_, sizeof(int), 1, fp);
        fread(&obj.month_, sizeof(int), 1, fp);
        fread(&obj.sex_, sizeof(char), 1, fp);
        if (obj.IsExist_)
        {
            TreeID_.insert(obj);
            TreeName_.insert(obj);
        }
        if (obj.offset_ + sizeof(bool)+sizeof(int)* 5 + obj.Length_ + sizeof(char) == nEnd)
        {
            break;
        }
    }
}

/*
修改文件中数据
参数一：引用的学生类
无返回值
*/
void CMyFile::ModifyState(CStudent &obj)
{
    FILE *fp = fopen("..//MyData.bin", "rb+");
    if (fp == nullptr)
    {
        throw "CMyFile::ModifyState() error:fopen";
    }

    fseek(fp, obj.offset_, SEEK_SET);
    fwrite(&obj.IsExist_, sizeof(bool), 1, fp);
    fclose(fp);
}

/*
通过ID比较
参数一：引用的学生类，参数二：引用的学生类
返回值：两个学生id的差值
*/
int compareID(CStudent& obj1, CStudent& obj2)
{
    return obj1.id_ - obj2.id_;
}

/*
通过姓名比较
参数一：引用的学生类，参数二：引用的学生类
返回值：两个学生姓名的比较值
*/
int compareName(CStudent& obj1, CStudent& obj2)
{
    return obj1.name_.Compare(obj2.name_);
}