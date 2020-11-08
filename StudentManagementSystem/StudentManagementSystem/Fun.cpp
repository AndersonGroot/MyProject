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
��ʾ�˵�
�޲���
�޷���ֵ
*/
void showMenu()
{
    cout << "           ѧ������ϵͳ" << endl;
    cout << "1.����ѧ����Ϣ" << endl;
    cout << "2.ɾ��ѧ����Ϣ" << endl;
    cout << "3.�޸�ѧ����Ϣ" << endl;
    cout << "4.��ѯѧ����Ϣ����ID��" << endl;
    cout << "5.��ѯѧ����Ϣ����������" << endl;
    cout << "6.�˳�" << endl;
    cout << endl;
    cout << "��ѡ��" << endl;
}

/*
ѡ����
����һ�����õ��ļ������
�޷���ֵ
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
        printf("���ӳɹ�\r\n");
        system("pause");
        break;
    case 2:
        deleteInformation(obj);
        printf("ɾ���ɹ�\r\n");
        system("pause");
        break;
    case 3:
        modifyInformation(obj);
        printf("�޸ĳɹ�\r\n");
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
���
����һ�����õ��ļ������
�޷���ֵ
*/
void addInformation(CMyFile &obj)
{
    CStudent stu;
    char szID[8] = "\0";
    char szName[32] = "\0";
    char szYear[8] = "\0";
    char szMonth[4] = "\0";
    char szSex[8] = "\0";
    //����ID
    while (true)
    {
        printf("��¼����ѧ��ID�����7λ��,����������������ַ�֮�󲿷��Զ����ԣ���\r\n");
        fflush(stdin);
        while (scanf("%7[0-9]s", szID) == 0)
        {
            fflush(stdin);
            printf("�����������������ID��\r\n");
        }
        fflush(stdin);
        //�ַ���תint
        sscanf(szID, "%d", &stu.id_);
        if (obj.TreeID_.find(stu) != nullptr)
        {
            printf("���и�ID,����������\r\n");
            continue;
        }
        
        break;
    }

    //��������
    printf("������ѧ�����������31��Ӣ���ַ�,���������Զ����ԣ���\r\n");
    fflush(stdin);
    while (scanf("%31[^\n]s", szName) == 0)
    {
        fflush(stdin);
        printf("�����������������������\r\n");
    }
    fflush(stdin);
    stu.name_ = szName;
   
    //�������
    while (true)
    {
        printf("������ѧ��������ݣ�1900-2019,����������������ַ�֮�󲿷��Զ����ԣ���\r\n");
        fflush(stdin);
        while (scanf("%4[0-9]s", szYear) == 0)
        {
            fflush(stdin);
            printf("����������������������ݣ�\r\n");
        }
        fflush(stdin);
        // �ַ���תint
        sscanf(szYear, "%d", &stu.year_);
        if (stu.year_<1900 || stu.year_>2019)
        {
            printf("������Ч,����������������\r\n");
            continue;
        }

        break;
    }

    //�����·�
    while (true)
    {
        printf("������ѧ�������·ݣ�1-12,����������������ַ�֮�󲿷��Զ����ԣ���\r\n");
        fflush(stdin);
        while (scanf("%2[0-9]s", szMonth) == 0)
        {
            fflush(stdin);
            printf("���������������������·ݣ�");
        }
        fflush(stdin);
        // �ַ���תint
        sscanf(szMonth, "%d", &stu.month_);
        if (stu.month_<1 || stu.month_>12)
        {
            printf("������Ч,��������������·�\r\n");
            continue;
        }
        if (stu.year_ == 2019 && stu.month_ > 9)
        {
            printf("������Ч,��������������·�\r\n");
            continue;
        }

        break;
    }

    //�����Ա�
    while (true)
    {
        printf("������ѧ���Ա��У�Ů��δ֪����������");
        fflush(stdin);
        while (scanf("%5[^\n]s", szSex) == 0)
        {
            fflush(stdin);
            printf("������������������Ա�");
        }
        fflush(stdin);
        char *pMale = "��";
        char *pFemale = "Ů";
        char *pUnkown = "δ֪";
        char *pOther = "����";
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
            printf("������Ч,�����������Ա�\r\n");
        }
    }
    
    //����ID��
    obj.TreeID_.insert(stu);
    //����������
    obj.TreeName_.insert(stu);
    //д���ļ�
    obj.Write(stu);
}

/*
ɾ��
����һ�����õ��ļ������
�޷���ֵ
*/
void deleteInformation(CMyFile &obj)
{
    CStudent stu;
    char szID[8] = "\0";
    //����ID
    while (true)
    {
        printf("������ѧ��ID�����7λ��,����������������ַ�֮�󲿷��Զ����ԣ���\r\n");
        fflush(stdin);
        while (scanf("%7[0-9]s", szID) == 0)
        {
            fflush(stdin);
            printf("�����������������ID��\r\n");
        }
        fflush(stdin);
        //�ַ���תint
        sscanf(szID, "%d", &stu.id_);
        if (obj.TreeID_.find(stu) == nullptr)
        {
            printf("û�и�ID,����������\r\n");
            continue;
        }

        //������ѧ����Ϣ
        stu = obj.TreeID_.find(stu)->elem_;
        stu.IsExist_ = false;

        if (obj.TreeID_.IsEmpty())
        {
            printf("��������");
            return;
        }

        //ID�����Ƴ������ڵ�
        obj.TreeID_.remove(obj.TreeID_.find(stu)->elem_);

        //�������ֻ����һ�����֣��Ƴ������ڵ�
        if (obj.TreeName_.find(stu)->next_ == nullptr)
        {
            obj.TreeName_.remove(stu);
        }
        //����ж�����֣����������ҵ�IDһ���Ľڵ㣬�Ƴ�������ڵ�
        else
        {
            CMyAVLTree<CStudent>::TreeNode *node = obj.TreeName_.find(stu);
            CMyAVLTree<CStudent>::TreeNode *oldNode = nullptr;
            while (node)
            {
                //�ҵ��ýڵ�
                if (node->elem_.id_ == stu.id_)
                {
                    //�����ͷ�ڵ�
                    if (node == obj.TreeName_.find(stu))
                    {
                        node->next_->left_ = node->left_;
                        node->next_->right_ = node->right_;
                        node->next_->height_ = node->height_;
                        node->next_->parent_ = node->parent_;
                        //����Ǹ��ڵ���Һ���
                        if (node->parent_->right_ == node)
                        {
                            //�Ѹ��ڵ��Һ���ָ��ýڵ����һ��
                            node->parent_->right_ = node->next_;
                        }
                        //����Ǹ��ڵ������
                        else
                        {
                            //�Ѹ��ڵ�����ָ��ýڵ����һ��
                            node->parent_->left_ = node->next_;
                        }
                        node->next_ = nullptr;
                        delete node;
                        break;
                    }
                    //������м�Ľڵ㣬�ýڵ��ǰһ���ڵ�ָ��ýڵ�ĺ�һ���ڵ㣬�Ƴ��ýڵ�
                    else
                    {
                        oldNode->next_ = node->next_;
                        node->next_ = nullptr;
                        delete node;
                        break;
                    }
                }
                //����ýڵ㣬��������һ������ڵ�
                oldNode = node;
                node = node->next_;
            }
        }


        break;
    }
    //�ļ���޸ĸ���Ϣ�Ĵ���״̬
    obj.ModifyState(stu);
}

/*
�޸�
����һ�����õ��ļ���
�޷���ֵ
*/
void modifyInformation(CMyFile &obj)
{
    deleteInformation(obj);
    addInformation(obj);
}


/*
��ѧ�Ų���
����һ�����õ��ļ���
�޷���ֵ
*/
void findInformationID(CMyFile &obj)
{
    CStudent stu;
    char szID[8] = "\0";
    //����ID
    while (true)
    {
        printf("������ѧ��ID�����7λ��,����������������ַ�֮�󲿷��Զ����ԣ���\r\n");
        fflush(stdin);
        while (scanf("%7[0-9]s", szID) == 0)
        {
            fflush(stdin);
            printf("�����������������ID��\r\n");
        }
        fflush(stdin);
        //�ַ���תint
        sscanf(szID, "%d", &stu.id_);
        if (obj.TreeID_.find(stu) == nullptr)
        {
            printf("û�и�ID,����������\r\n");
            continue;
        }

        break;
    }

    //��ʾ�ҵ���ѧ����Ϣ
    showInformation(obj.TreeID_.find(stu)->elem_);
}

/*
����������
����һ�����õ��ļ���
�޷���ֵ
*/
void findInformationName(CMyFile &obj)
{
    CStudent stu;
    char szName[32] = "\0";
    //��������
    printf("������ѧ�����������31��Ӣ���ַ�,���������Զ����ԣ���\r\n");
    fflush(stdin);
    while (scanf("%31[^\n]s", szName) == 0)
    {
        fflush(stdin);
        printf("�����������������������\r\n");
    }
    fflush(stdin);
    stu.name_ = szName;

    CMyAVLTree<CStudent>::TreeNode *node = obj.TreeName_.find(stu);
    //��ʾ�ҵ���ѧ����Ϣ�������������ʾ���������е�ѧ����Ϣ
    while (node)
    {
        showInformation(node->elem_);
        node = node->next_;
    }

    cout << "δ�ҵ�������ѧ��" << endl;
}

/*
��ʾѧ����Ϣ
����һ��ѧ����
�޷���ֵ
*/
void showInformation(CStudent &obj)
{
    cout << "ID:" << obj.id_ << endl;
    cout << "����:" << obj.name_ << endl;
    cout << "��������:" << obj.year_ << '/' << obj.month_ << endl;
    if (obj.sex_ == '0')
    {
        cout << "�Ա�:" << "��" << endl;
    }
    else if (obj.sex_ == '1')
    {
        cout << "�Ա�:" << "Ů" << endl;
    }
    else if (obj.sex_ == '2')
    {
        cout << "�Ա�:" << "δ֪" << endl;
    }
    else if (obj.sex_ == '3')
    {
        cout << "�Ա�:" << "����" << endl;
    }
    cout << endl;
}