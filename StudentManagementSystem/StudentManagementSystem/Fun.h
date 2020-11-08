#pragma once
#include "Fun.h"
#include "MyString.h"
#include "MyAVLTree.h"
#include "Student.h"
#include "MyFile.h"

//显示菜单
void showMenu();
//选择功能
void select(CMyFile &obj);
//增加
void addInformation(CMyFile &obj);
//删除
void deleteInformation(CMyFile &obj);
//修改
void modifyInformation(CMyFile &obj);
//按ID查找
void findInformationID(CMyFile &obj);
//按姓名查找
void findInformationName(CMyFile &obj);
//显示信息
void showInformation(CStudent &obj);
