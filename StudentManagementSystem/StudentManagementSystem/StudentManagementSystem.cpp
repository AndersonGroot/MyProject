// StudentManagementSystem.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "MyString.h"
#include "MyAVLTree.h"
#include "Student.h"
#include "MyFile.h"
#include "Fun.h"
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    cout << "����������..." << endl;
    try
    {
        CMyFile student;
        student.Read();

        while (true)
        {
            system("CLS");
            showMenu();
            select(student);
        }
    }
    catch (char* error)
    {
        cout << error << endl;
    }

    

	return 0;
}

