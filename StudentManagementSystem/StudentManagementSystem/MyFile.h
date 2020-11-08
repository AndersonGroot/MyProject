#pragma once
#include "Student.h"
#include "MyAVLTree.h"

//�ļ���
class CMyFile
{
public:
    CMyFile();
    ~CMyFile();
    //д������
    void Write(CStudent &obj);
    //��ȡ����
    void Read();
    //�޸��ļ�����
    void ModifyState(CStudent &obj);
public:
    //ID��
    CMyAVLTree<CStudent> TreeID_;
    //������
    CMyAVLTree<CStudent> TreeName_;
};

//��ID�Ƚϴ�С
int compareID(CStudent& obj1, CStudent& obj2);
//�������Ƚϴ�С
int compareName(CStudent& obj1, CStudent& obj2);
