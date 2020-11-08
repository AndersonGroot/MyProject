#include "stdafx.h"
#include "Fun.h"
#include "MyString.h"
#include "MyAVLTree.h"
#include "Student.h"
#include "MyFile.h"
#include <stdlib.h>
#include <iostream>
using namespace std;


/*
显示菜单
无参数
无返回值
*/
void showMenu()
{
    cout << "           学生管理系统" << endl;
    cout << "1.增加学生信息" << endl;
    cout << "2.删除学生信息" << endl;
    cout << "3.修改学生信息" << endl;
    cout << "4.查询学生信息（按ID）" << endl;
    cout << "5.查询学生信息（按姓名）" << endl;
    cout << "6.退出" << endl;
    cout << endl;
    cout << "请选择：" << endl;
}

/*
选择功能
参数一：引用的文件类对象
无返回值
*/
void select(CMyFile &obj)
{
    int n = 0;
    fflush(stdin);
    scanf("%d", &n);
    fflush(stdin);
    switch (n)
    {
    case 1:
        addInformation(obj);
        printf("增加成功\r\n");
        system("pause");
        break;
    case 2:
        deleteInformation(obj);
        printf("删除成功\r\n");
        system("pause");
        break;
    case 3:
        modifyInformation(obj);
        printf("修改成功\r\n");
        system("pause");
        break;
    case 4:
        findInformationID(obj);
        system("pause");
        break;
    case 5:
        findInformationName(obj);
        system("pause");
        break;
    case 6:
        exit(0);
    default:
        break;
    }
}

/*
添加
参数一：引用的文件类对象
无返回值
*/
void addInformation(CMyFile &obj)
{
    CStudent stu;
    char szID[8] = "\0";
    char szName[32] = "\0";
    char szYear[8] = "\0";
    char szMonth[4] = "\0";
    char szSex[8] = "\0";
    //输入ID
    while (true)
    {
        printf("请录入新学生ID（最多7位数,超出部分与非数字字符之后部分自动忽略）：\r\n");
        fflush(stdin);
        while (scanf("%7[0-9]s", szID) == 0)
        {
            fflush(stdin);
            printf("输入错误，请重新输入ID：\r\n");
        }
        fflush(stdin);
        //字符串转int
        sscanf(szID, "%d", &stu.id_);
        if (obj.TreeID_.find(stu) != nullptr)
        {
            printf("已有该ID,请重新输入\r\n");
            continue;
        }
        
        break;
    }

    //输入姓名
    printf("请输入学生姓名（最多31个英文字符,超出部分自动忽略）：\r\n");
    fflush(stdin);
    while (scanf("%31[^\n]s", szName) == 0)
    {
        fflush(stdin);
        printf("输入错误，请重新输入姓名：\r\n");
    }
    fflush(stdin);
    stu.name_ = szName;
   
    //输入年份
    while (true)
    {
        printf("请输入学生出生年份（1900-2019,超出部分与非数字字符之后部分自动忽略）：\r\n");
        fflush(stdin);
        while (scanf("%4[0-9]s", szYear) == 0)
        {
            fflush(stdin);
            printf("输入错误，请重新输入出生年份：\r\n");
        }
        fflush(stdin);
        // 字符串转int
        sscanf(szYear, "%d", &stu.year_);
        if (stu.year_<1900 || stu.year_>2019)
        {
            printf("输入无效,请重新输入出生年份\r\n");
            continue;
        }

        break;
    }

    //输入月份
    while (true)
    {
        printf("请输入学生出生月份（1-12,超出部分与非数字字符之后部分自动忽略）：\r\n");
        fflush(stdin);
        while (scanf("%2[0-9]s", szMonth) == 0)
        {
            fflush(stdin);
            printf("输入错误，请重新输入出生月份：");
        }
        fflush(stdin);
        // 字符串转int
        sscanf(szMonth, "%d", &stu.month_);
        if (stu.month_<1 || stu.month_>12)
        {
            printf("输入无效,请重新输入出生月份\r\n");
            continue;
        }
        if (stu.year_ == 2019 && stu.month_ > 9)
        {
            printf("输入无效,请重新输入出生月份\r\n");
            continue;
        }

        break;
    }

    //输入性别
    while (true)
    {
        printf("请输入学生性别（男，女，未知，其他）：");
        fflush(stdin);
        while (scanf("%5[^\n]s", szSex) == 0)
        {
            fflush(stdin);
            printf("输入错误，请重新输入性别：");
        }
        fflush(stdin);
        char *pMale = "男";
        char *pFemale = "女";
        char *pUnkown = "未知";
        char *pOther = "其他";
        if (*szSex == *pMale)
        {
            stu.sex_ = '0';
            break;
        }
        else if (*szSex == *pFemale)
        {
            stu.sex_ = '1';
            break;
        }
        else if (*szSex == *pUnkown)
        {
            stu.sex_ = '2';
            break;
        }
        else if (*szSex == *pOther)
        {
            stu.sex_ = '3';
            break;
        }
        else
        {
            printf("输入无效,请重新输入性别\r\n");
        }
    }
    
    //插入ID树
    obj.TreeID_.insert(stu);
    //插入姓名树
    obj.TreeName_.insert(stu);
    //写入文件
    obj.Write(stu);
}

/*
删除
参数一：引用的文件类对象
无返回值
*/
void deleteInformation(CMyFile &obj)
{
    CStudent stu;
    char szID[8] = "\0";
    //输入ID
    while (true)
    {
        printf("请输入学生ID（最多7位数,超出部分与非数字字符之后部分自动忽略）：\r\n");
        fflush(stdin);
        while (scanf("%7[0-9]s", szID) == 0)
        {
            fflush(stdin);
            printf("输入错误，请重新输入ID：\r\n");
        }
        fflush(stdin);
        //字符串转int
        sscanf(szID, "%d", &stu.id_);
        if (obj.TreeID_.find(stu) == nullptr)
        {
            printf("没有该ID,请重新输入\r\n");
            continue;
        }

        //保留该学生信息
        stu = obj.TreeID_.find(stu)->elem_;
        stu.IsExist_ = false;

        if (obj.TreeID_.IsEmpty())
        {
            printf("暂无数据");
            return;
        }

        //ID树里移除该树节点
        obj.TreeID_.remove(obj.TreeID_.find(stu)->elem_);

        //姓名树里，只有这一个名字，移除该树节点
        if (obj.TreeName_.find(stu)->next_ == nullptr)
        {
            obj.TreeName_.remove(stu);
        }
        //如果有多个名字，在链表中找到ID一样的节点，移除该链表节点
        else
        {
            CMyAVLTree<CStudent>::TreeNode *node = obj.TreeName_.find(stu);
            CMyAVLTree<CStudent>::TreeNode *oldNode = nullptr;
            while (node)
            {
                //找到该节点
                if (node->elem_.id_ == stu.id_)
                {
                    //如果是头节点
                    if (node == obj.TreeName_.find(stu))
                    {
                        node->next_->left_ = node->left_;
                        node->next_->right_ = node->right_;
                        node->next_->height_ = node->height_;
                        node->next_->parent_ = node->parent_;
                        //如果是父节点的右孩子
                        if (node->parent_->right_ == node)
                        {
                            //把父节点右孩子指向该节点的下一个
                            node->parent_->right_ = node->next_;
                        }
                        //如果是父节点的左孩子
                        else
                        {
                            //把父节点左孩子指向该节点的下一个
                            node->parent_->left_ = node->next_;
                        }
                        node->next_ = nullptr;
                        delete node;
                        break;
                    }
                    //如果是中间的节点，该节点的前一个节点指向该节点的后一个节点，移除该节点
                    else
                    {
                        oldNode->next_ = node->next_;
                        node->next_ = nullptr;
                        delete node;
                        break;
                    }
                }
                //保存该节点，接着找下一个链表节点
                oldNode = node;
                node = node->next_;
            }
        }


        break;
    }
    //文件里，修改该信息的存在状态
    obj.ModifyState(stu);
}

/*
修改
参数一：引用的文件类
无返回值
*/
void modifyInformation(CMyFile &obj)
{
    deleteInformation(obj);
    addInformation(obj);
}


/*
按学号查找
参数一：引用的文件类
无返回值
*/
void findInformationID(CMyFile &obj)
{
    CStudent stu;
    char szID[8] = "\0";
    //输入ID
    while (true)
    {
        printf("请输入学生ID（最多7位数,超出部分与非数字字符之后部分自动忽略）：\r\n");
        fflush(stdin);
        while (scanf("%7[0-9]s", szID) == 0)
        {
            fflush(stdin);
            printf("输入错误，请重新输入ID：\r\n");
        }
        fflush(stdin);
        //字符串转int
        sscanf(szID, "%d", &stu.id_);
        if (obj.TreeID_.find(stu) == nullptr)
        {
            printf("没有该ID,请重新输入\r\n");
            continue;
        }

        break;
    }

    //显示找到的学生信息
    showInformation(obj.TreeID_.find(stu)->elem_);
}

/*
按姓名查找
参数一：引用的文件类
无返回值
*/
void findInformationName(CMyFile &obj)
{
    CStudent stu;
    char szName[32] = "\0";
    //输入姓名
    printf("请输入学生姓名（最多31个英文字符,超出部分自动忽略）：\r\n");
    fflush(stdin);
    while (scanf("%31[^\n]s", szName) == 0)
    {
        fflush(stdin);
        printf("输入错误，请重新输入姓名：\r\n");
    }
    fflush(stdin);
    stu.name_ = szName;

    CMyAVLTree<CStudent>::TreeNode *node = obj.TreeName_.find(stu);
    //显示找到的学生信息，如果是链表，显示链表中所有的学生信息
    while (node)
    {
        showInformation(node->elem_);
        node = node->next_;
    }

    cout << "未找到该姓名学生" << endl;
}

/*
显示学生信息
参数一：学生类
无返回值
*/
void showInformation(CStudent &obj)
{
    cout << "ID:" << obj.id_ << endl;
    cout << "姓名:" << obj.name_ << endl;
    cout << "出生年月:" << obj.year_ << '/' << obj.month_ << endl;
    if (obj.sex_ == '0')
    {
        cout << "性别:" << "男" << endl;
    }
    else if (obj.sex_ == '1')
    {
        cout << "性别:" << "女" << endl;
    }
    else if (obj.sex_ == '2')
    {
        cout << "性别:" << "未知" << endl;
    }
    else if (obj.sex_ == '3')
    {
        cout << "性别:" << "其他" << endl;
    }
    cout << endl;
}