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
д�����ݵ��ļ���
����һ�����õ�ѧ����
�޷���ֵ
*/
void CMyFile::Write(CStudent &obj)
{
    //β����ӷ�ʽ�������ļ�
    FILE *fp = fopen("..//MyData.bin", "ab+");
    if (fp == nullptr)
    {
        throw "CMyFile::Write() error:fopen";
    }
    obj.Length_ = obj.name_.getLimit() + 1;
    //��ȡƫ����
    fseek(fp, 0, SEEK_END);
    obj.offset_ = ftell(fp);
    //д��ѧ����Ϣ
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
���ļ��ж�ȡ����
�޲���
�޷���ֵ
*/
void CMyFile::Read()
{
    CStudent obj;
    //�����ƶ�д��ʽ���ļ�
    FILE *fp = fopen("..//MyData.bin", "rb+");
    if (fp == nullptr)
    {
        throw "CMyFile::Read() error:fopen";
    }
    char szBuff[1024] = { 0 }; //����һ��������
    //��ȡ�ļ�β
    fseek(fp, 0, SEEK_END);
    unsigned int nEnd = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    while (true)
    {
        fread(&obj.IsExist_, sizeof(bool), 1, fp);
        fread(&obj.offset_, sizeof(int), 1, fp);
        fread(&obj.Length_, sizeof(int), 1, fp);
        fread(&obj.id_, sizeof(int), 1, fp);
        //��ȡ������������
        fread(szBuff, obj.Length_, 1, fp);
        //�������������ݸ�CMyString�Ķ��󣬱�������ʱ���ͷ�����
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
�޸��ļ�������
����һ�����õ�ѧ����
�޷���ֵ
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
ͨ��ID�Ƚ�
����һ�����õ�ѧ���࣬�����������õ�ѧ����
����ֵ������ѧ��id�Ĳ�ֵ
*/
int compareID(CStudent& obj1, CStudent& obj2)
{
    return obj1.id_ - obj2.id_;
}

/*
ͨ�������Ƚ�
����һ�����õ�ѧ���࣬�����������õ�ѧ����
����ֵ������ѧ�������ıȽ�ֵ
*/
int compareName(CStudent& obj1, CStudent& obj2)
{
    return obj1.name_.Compare(obj2.name_);
}