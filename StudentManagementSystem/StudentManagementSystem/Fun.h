#pragma once
#include "Fun.h"
#include "MyString.h"
#include "MyAVLTree.h"
#include "Student.h"
#include "MyFile.h"

//��ʾ�˵�
void showMenu();
//ѡ����
void select(CMyFile &obj);
//����
void addInformation(CMyFile &obj);
//ɾ��
void deleteInformation(CMyFile &obj);
//�޸�
void modifyInformation(CMyFile &obj);
//��ID����
void findInformationID(CMyFile &obj);
//����������
void findInformationName(CMyFile &obj);
//��ʾ��Ϣ
void showInformation(CStudent &obj);
