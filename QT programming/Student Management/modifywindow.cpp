#include "modifywindow.h"
#include "ui_modifywindow.h"
#include "mainwindow.h"
#include <QMessageBox>

ModifyWindow::ModifyWindow( MainWindow *pthis,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModifyWindow)
{
    ui->setupUi(this);
    m_pthis=pthis ;

    //学生姓名长度不超过8
    ui->txt_stuName->setMaxLength(8);
    //课程名长度不超过16
    ui->Txt_LesName->setMaxLength(16);
    //初始化下拉框
    //显示学生
    for(int i=0;i<m_pthis->m_StudentList.size();i++)
    {
        QString tempId=m_pthis->m_StudentList[i].qsStudentId;
        QString tempName=m_pthis->m_StudentList[i].qsStudentName;
        ui->cmb_stuId->addItem(tempId);
       // ui->del_cmb_seleStuId->addItem(tempId);
        //ui->del_cmb_stuName->addItem(tempName);
    }

    //显示课程
    for(int i=0;i<m_pthis->m_LessonList.size();i++)
    {
        QString tempId=m_pthis->m_LessonList[i].qsLessonId;
        QString tempName=m_pthis->m_LessonList[i].qsLessonName;
        ui->cmb_lesId->addItem(tempId);
       // ui->del_cmb_stuName->addItem(tempName);
    }
}

ModifyWindow::~ModifyWindow()
{
    delete ui;
}

void ModifyWindow::clickedModifyBtn(bool)
{
    //如果没有学生
    if(m_pthis->m_StudentList.isEmpty())
    {
        QMessageBox::about(this,"提示","没有学生");
        return;
    }
    //修改学生链表中的学生姓名
    int pos = ui->cmb_stuId->currentIndex();
    QString stuPos=ui->cmb_stuId->currentText();
    QString stuName = ui->txt_stuName->text();

    //判断用户是 否输入
    if(stuName==nullptr)
    {
         QMessageBox::about(this,"提示","请输入要修改的学生姓名");
         return;
    }

    m_pthis->m_StudentList[pos].qsStudentName = stuName;


    //修改选课链表中的学生姓名
    for(int i = 0;i < m_pthis->m_SelectionList.size();i++)
    {
        if(m_pthis->m_SelectionList[i].m_studentz.qsStudentId == stuPos)
        {
            m_pthis->m_SelectionList[i].m_studentz.qsStudentName = stuName;
            break;
        }
    }
    QMessageBox::about(this,"提示","学生姓名修改成功");
}

void ModifyWindow::clickedModifyBtn2(bool)
{
    //如果没有课程
        if(m_pthis->m_LessonList.isEmpty())
        {
            QMessageBox::about(this,"提示","没有课程");
            return;
        }
        //修改课程链表中的课程名
        int pos = ui->cmb_lesId->currentIndex();
        QString subPos = ui->cmb_lesId->currentText();
        QString subName = ui->Txt_LesName->text();
        //判断用户是 否输入
        if(subName==nullptr)
        {
             QMessageBox::about(this,"提示","请输入要修改的课程名");
             return ;
        }

        m_pthis->m_LessonList[pos].qsLessonName = subName;


        //修改选课链表中的课程名
        for(int i = 0;i < m_pthis->m_SelectionList.size();i++)
        {
            for(int j = 0;j < m_pthis->m_SelectionList[i].m_lesson.size();j++)
            {
                if(m_pthis->m_SelectionList[i].m_lesson[j].qsLessonId == subPos)
                {
                    m_pthis->m_SelectionList[i].m_lesson[j].qsLessonName = subName;
                    break;
                }
            }
        }
        QMessageBox::about(this,"提示","课程名修改成功");

}
