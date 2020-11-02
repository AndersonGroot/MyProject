#include "cmyfindwindow.h"
#include "ui_cmyfindwindow.h"
#include "mainwindow.h"
#include <QMessageBox>

CMyFindWindow::CMyFindWindow(MainWindow *pthis,  QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CMyFindWindow)
{
    ui->setupUi(this);
    m_pthis = pthis;
    //设置正则表达式，学生id可接受字母，数字类型的数据，但不超过11个
    QRegExp regExpID("[A-Za-z0-9]{1,11}");
    ui->txt_stuId->setValidator(new QRegExpValidator(regExpID, this));
    ui->txt_seletStu->setValidator(new QRegExpValidator(regExpID, this));
    //设置正则表达式，课程id可接受字母，数字类型的数据，但不超过11个
    ui->txt_subId->setValidator(new QRegExpValidator(regExpID, this));
    ui->txt_seletSubId->setValidator(new QRegExpValidator(regExpID, this));
    //学生姓名长度不超过8
    ui->txt_stuName->setMaxLength(8);
    //课程名长度不超过16
    ui->txt_subName->setMaxLength(16);
    ui->txt_seletSubName->setMaxLength(16);
}

CMyFindWindow::~CMyFindWindow()
{
    delete ui;
}

void CMyFindWindow::stuInfoFindSlots(bool)
{
    //记录学生ID
    m_text = ui->txt_stuId->text();
    //记下表格的行数
    int nCount = 0;
    //设置列宽
    ui->tableWidget->setColumnWidth(0,70);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,70);
    ui->tableWidget->setColumnWidth(3,100);
    ui->tableWidget->setColumnWidth(4,50);
    //设置行数
    ui->tableWidget->setRowCount(nCount + 1);
    //画表头
    QTableWidgetItem *item1=new QTableWidgetItem();
    item1->setText("ID");
    ui->tableWidget->setItem(nCount,0,item1);
    QTableWidgetItem *item2=new QTableWidgetItem();
    item2->setText("姓名");
    ui->tableWidget->setItem(nCount,1,item2);
    QTableWidgetItem *item3=new QTableWidgetItem();
    item3->setText("");
    ui->tableWidget->setItem(nCount,2,item3);
    QTableWidgetItem *item4=new QTableWidgetItem();
    item4->setText("");
    ui->tableWidget->setItem(nCount,3,item4);
    QTableWidgetItem *item5=new QTableWidgetItem();
    item5->setText("");
    ui->tableWidget->setItem(nCount,4,item5);
    //遍历链表，模糊查找学生ID
    for(int i = 0;i < m_pthis->m_StudentList.size();i++)
    {
        if(m_pthis->m_StudentList[i].qsStudentId.contains(m_text))
        {
            nCount++;
            ui->tableWidget->setRowCount(nCount + 1);
            QTableWidgetItem *item1=new QTableWidgetItem();
            item1->setText(m_pthis->m_StudentList[i].qsStudentId);
            ui->tableWidget->setItem(nCount,0,item1);
            QTableWidgetItem *item2=new QTableWidgetItem();
            item2->setText(m_pthis->m_StudentList[i].qsStudentName);
            ui->tableWidget->setItem(nCount,1,item2);
        }
    }
    //如果没有找到，只画表头
    if(nCount == 0)
    {
        ui->tableWidget->setRowCount(nCount + 1);
    }
}

void CMyFindWindow::subInfoFindSlots(bool)
{
    //记录课程ID
    m_text = ui->txt_subId->text();

    //记下表格的行数
    int nCount = 0;
    //设置列宽
    ui->tableWidget->setColumnWidth(0,70);
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,70);
    ui->tableWidget->setColumnWidth(3,70);
    ui->tableWidget->setColumnWidth(4,50);
    //设置行数
    ui->tableWidget->setRowCount(nCount + 1);
    //画表头
    QTableWidgetItem *item1=new QTableWidgetItem();
    item1->setText("ID");
    ui->tableWidget->setItem(nCount,0,item1);
    QTableWidgetItem *item2=new QTableWidgetItem();
    item2->setText("课程");
    QTableWidgetItem *item3=new QTableWidgetItem();
    item3->setText("");
    ui->tableWidget->setItem(nCount,2,item3);
    QTableWidgetItem *item4=new QTableWidgetItem();
    item4->setText("");
    ui->tableWidget->setItem(nCount,3,item4);
    QTableWidgetItem *item5=new QTableWidgetItem();
    item5->setText("");
    ui->tableWidget->setItem(nCount,4,item5);
    ui->tableWidget->setItem(nCount,1,item2);

    //遍历链表，模糊查找课程ID
    for(int i = 0;i < m_pthis->m_LessonList.size();i++)
    {
        if(m_pthis->m_LessonList[i].qsLessonId.contains(m_text))
        {
            nCount++;
            ui->tableWidget->setRowCount(nCount + 1);
            QTableWidgetItem *item1=new QTableWidgetItem();
            item1->setText(m_pthis->m_LessonList[i].qsLessonId);
            ui->tableWidget->setItem(nCount,0,item1);
            QTableWidgetItem *item2=new QTableWidgetItem();
            item2->setText(m_pthis->m_LessonList[i].qsLessonName);
            ui->tableWidget->setItem(nCount,1,item2);
        }
    }
    //如果没有找到，只画表头
    if(nCount == 0)
    {
        ui->tableWidget->setRowCount(nCount + 1);
    }
}

void CMyFindWindow::selSubInfoFindSlots(bool)
{
    //记录课程ID
    m_subId = ui->txt_seletSubId->text();
    //记下表格的行数
    int nCount = 0;
    //设置列宽
    ui->tableWidget->setColumnWidth(0,70);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,70);
    ui->tableWidget->setColumnWidth(3,150);
    ui->tableWidget->setColumnWidth(4,50);
    //设置行数
    ui->tableWidget->setRowCount(nCount + 1);
    //画表头
    QTableWidgetItem *item1=new QTableWidgetItem();
    item1->setText("学生id");
    ui->tableWidget->setItem(nCount,0,item1);
    QTableWidgetItem *item2=new QTableWidgetItem();
    item2->setText("姓名");
    ui->tableWidget->setItem(nCount,1,item2);
    QTableWidgetItem *item3=new QTableWidgetItem();
    item3->setText("课程id");
    ui->tableWidget->setItem(nCount,2,item3);
    QTableWidgetItem *item4=new QTableWidgetItem();
    item4->setText("课程");
    ui->tableWidget->setItem(nCount,3,item4);
    QTableWidgetItem *item5=new QTableWidgetItem();
    item5->setText("分数");
    ui->tableWidget->setItem(nCount,4,item5);
    //遍历选课链表
    for(int i = 0;i < m_pthis->m_SelectionList.size();i++)
    {
        //遍历课程链表，精确查找课程ID
        for(int j = 0;j < m_pthis->m_SelectionList[i].m_lesson.size();j++)
        {
            //显示找到的信息
            if(m_pthis->m_SelectionList[i].m_lesson[j].qsLessonId == m_subId)
            {
                nCount++;
                ui->tableWidget->setRowCount(nCount + 1);
                QTableWidgetItem *item1=new QTableWidgetItem();
                item1->setText(m_pthis->m_SelectionList[i].m_studentz.qsStudentId);
                ui->tableWidget->setItem(nCount,0,item1);
                QTableWidgetItem *item2=new QTableWidgetItem();
                item2->setText(m_pthis->m_SelectionList[i].m_studentz.qsStudentName);
                ui->tableWidget->setItem(nCount,1,item2);
                QTableWidgetItem *item3=new QTableWidgetItem();
                item3->setText(m_pthis->m_SelectionList[i].m_lesson[j].qsLessonId);
                ui->tableWidget->setItem(nCount,2,item3);
                QTableWidgetItem *item4=new QTableWidgetItem();
                item4->setText(m_pthis->m_SelectionList[i].m_lesson[j].qsLessonName);
                ui->tableWidget->setItem(nCount,3,item4);
                QTableWidgetItem *item5=new QTableWidgetItem();
                item5->setText(m_pthis->m_SelectionList[i].m_score[j]);
                ui->tableWidget->setItem(nCount,4,item5);
            }
        }

    }
    //如果没有找到，只画表头
    if(nCount == 0)
    {
        ui->tableWidget->setRowCount(nCount + 1);
    }
}

void CMyFindWindow::stuIdFindSlots(bool)
{
    //记录学生姓名
    m_text = ui->txt_stuName->text();
    //记下表格的行数
    int nCount = 0;
    //设置列宽
    ui->tableWidget->setColumnWidth(0,70);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,70);
    ui->tableWidget->setColumnWidth(3,100);
    ui->tableWidget->setColumnWidth(4,50);
    //设置行数
    ui->tableWidget->setRowCount(nCount + 1);
    //画表头
    QTableWidgetItem *item1=new QTableWidgetItem();
    item1->setText("ID");
    ui->tableWidget->setItem(nCount,0,item1);
    QTableWidgetItem *item2=new QTableWidgetItem();
    item2->setText("姓名");
    ui->tableWidget->setItem(nCount,1,item2);
    QTableWidgetItem *item3=new QTableWidgetItem();
    item3->setText("");
    ui->tableWidget->setItem(nCount,2,item3);
    QTableWidgetItem *item4=new QTableWidgetItem();
    item4->setText("");
    ui->tableWidget->setItem(nCount,3,item4);
    QTableWidgetItem *item5=new QTableWidgetItem();
    item5->setText("");
    ui->tableWidget->setItem(nCount,4,item5);
    //遍历链表，模糊查找姓名
    for(int i = 0;i < m_pthis->m_StudentList.size();i++)
    {
        if(m_pthis->m_StudentList[i].qsStudentName.contains(m_text))
        {
            nCount++;
            ui->tableWidget->setRowCount(nCount + 1);
            QTableWidgetItem *item1=new QTableWidgetItem();
            item1->setText(m_pthis->m_StudentList[i].qsStudentId);
            ui->tableWidget->setItem(nCount,0,item1);
            QTableWidgetItem *item2=new QTableWidgetItem();
            item2->setText(m_pthis->m_StudentList[i].qsStudentName);
            ui->tableWidget->setItem(nCount,1,item2);
        }
    }
    //如果没有找到，只画表头
    if(nCount == 0)
    {
        ui->tableWidget->setRowCount(nCount + 1);
    }
}

void CMyFindWindow::subIdFindSlots(bool)
{
    //记录课程ID
    m_text = ui->txt_subName->text();
    //记下表格的行数
    int nCount = 0;
    //设置列宽
    ui->tableWidget->setColumnWidth(0,70);
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,70);
    ui->tableWidget->setColumnWidth(3,70);
    ui->tableWidget->setColumnWidth(4,50);
    //设置行数
    ui->tableWidget->setRowCount(nCount + 1);
    //画表头
    QTableWidgetItem *item1=new QTableWidgetItem();
    item1->setText("ID");
    ui->tableWidget->setItem(nCount,0,item1);
    QTableWidgetItem *item2=new QTableWidgetItem();
    item2->setText("课程");
    ui->tableWidget->setItem(nCount,1,item2);
    QTableWidgetItem *item3=new QTableWidgetItem();
    item3->setText("");
    ui->tableWidget->setItem(nCount,2,item3);
    QTableWidgetItem *item4=new QTableWidgetItem();
    item4->setText("");
    ui->tableWidget->setItem(nCount,3,item4);
    QTableWidgetItem *item5=new QTableWidgetItem();
    item5->setText("");
    ui->tableWidget->setItem(nCount,4,item5);
    //遍历链表，模糊查找课程
    for(int i = 0;i < m_pthis->m_LessonList.size();i++)
    {
        if(m_pthis->m_LessonList[i].qsLessonName.contains(m_text))
        {
            nCount++;
            ui->tableWidget->setRowCount(nCount + 1);
            QTableWidgetItem *item1=new QTableWidgetItem();
            item1->setText(m_pthis->m_LessonList[i].qsLessonId);
            ui->tableWidget->setItem(nCount,0,item1);
            QTableWidgetItem *item2=new QTableWidgetItem();
            item2->setText(m_pthis->m_LessonList[i].qsLessonName);
            ui->tableWidget->setItem(nCount,1,item2);
        }
    }
    //如果没有找到，只画表头
    if(nCount == 0)
    {
        ui->tableWidget->setRowCount(nCount + 1);
    }
}

void CMyFindWindow::selStuInfoFindSlots(bool)
{
    //记录学生ID
    m_text = ui->txt_seletStu->text();
    //记下表格的行数
    int nCount = 0;
    //设置列宽
    ui->tableWidget->setColumnWidth(0,70);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,70);
    ui->tableWidget->setColumnWidth(3,150);
    ui->tableWidget->setColumnWidth(4,50);
    //设置行数
    ui->tableWidget->setRowCount(nCount + 1);
    //画表头
    QTableWidgetItem *item1=new QTableWidgetItem();
    item1->setText("学生id");
    ui->tableWidget->setItem(nCount,0,item1);
    QTableWidgetItem *item2=new QTableWidgetItem();
    item2->setText("姓名");
    ui->tableWidget->setItem(nCount,1,item2);
    QTableWidgetItem *item3=new QTableWidgetItem();
    item3->setText("课程id");
    ui->tableWidget->setItem(nCount,2,item3);
    QTableWidgetItem *item4=new QTableWidgetItem();
    item4->setText("课程");
    ui->tableWidget->setItem(nCount,3,item4);
    QTableWidgetItem *item5=new QTableWidgetItem();
    item5->setText("分数");
    ui->tableWidget->setItem(nCount,4,item5);
    //遍历选课链表
    for(int i = 0;i < m_pthis->m_SelectionList.size();i++)
    {
        if(m_pthis->m_SelectionList[i].m_studentz.qsStudentId == m_text)
        {
            //遍历显示选课信息
            for(int j = 0;j < m_pthis->m_SelectionList[i].m_lesson.size();j++)
            {
                nCount++;
                ui->tableWidget->setRowCount(nCount + 1);
                QTableWidgetItem *item1=new QTableWidgetItem();
                item1->setText(m_pthis->m_SelectionList[i].m_studentz.qsStudentId);
                ui->tableWidget->setItem(nCount,0,item1);
                QTableWidgetItem *item2=new QTableWidgetItem();
                item2->setText(m_pthis->m_SelectionList[i].m_studentz.qsStudentName);
                ui->tableWidget->setItem(nCount,1,item2);
                QTableWidgetItem *item3=new QTableWidgetItem();
                item3->setText(m_pthis->m_SelectionList[i].m_lesson[j].qsLessonId);
                ui->tableWidget->setItem(nCount,2,item3);
                QTableWidgetItem *item4=new QTableWidgetItem();
                item4->setText(m_pthis->m_SelectionList[i].m_lesson[j].qsLessonName);
                ui->tableWidget->setItem(nCount,3,item4);
                QTableWidgetItem *item5=new QTableWidgetItem();
                item5->setText(m_pthis->m_SelectionList[i].m_score[j]);
                ui->tableWidget->setItem(nCount,4,item5);
            }
        }
    }
    //如果没有找到，只画表头
    if(nCount == 0)
    {
        ui->tableWidget->setRowCount(nCount + 1);
    }
}

void CMyFindWindow::selSubFindSlots(bool)
{
    //记录课程名
    m_text = ui->txt_seletSubName->text();
    //记下表格的行数
    int nCount = 0;
    //设置列宽
    ui->tableWidget->setColumnWidth(0,70);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,70);
    ui->tableWidget->setColumnWidth(3,70);
    ui->tableWidget->setColumnWidth(4,50);
    //设置行数
    ui->tableWidget->setRowCount(nCount + 1);
    //画表头
    QTableWidgetItem *item1=new QTableWidgetItem();
    item1->setText("学生id");
    ui->tableWidget->setItem(nCount,0,item1);
    QTableWidgetItem *item2=new QTableWidgetItem();
    item2->setText("姓名");
    ui->tableWidget->setItem(nCount,1,item2);
    QTableWidgetItem *item3=new QTableWidgetItem();
    item3->setText("成绩");
    ui->tableWidget->setItem(nCount,2,item3);
    QTableWidgetItem *item4=new QTableWidgetItem();
    item4->setText("");
    ui->tableWidget->setItem(nCount,3,item4);
    QTableWidgetItem *item5=new QTableWidgetItem();
    item5->setText("");
    ui->tableWidget->setItem(nCount,4,item5);

    //遍历选课链表
    for(int i = 0;i < m_pthis->m_SelectionList.size();i++)
    {
        //遍历课程链表，精确查找课程名
        for(int j = 0;j < m_pthis->m_SelectionList[i].m_lesson.size();j++)
        {
            //显示找到的信息
            if(m_pthis->m_SelectionList[i].m_lesson[j].qsLessonName == m_text)
            {
                nCount++;
                ui->tableWidget->setRowCount(nCount + 1);
                QTableWidgetItem *item1=new QTableWidgetItem();
                item1->setText(m_pthis->m_SelectionList[i].m_studentz.qsStudentId);
                ui->tableWidget->setItem(nCount,0,item1);
                QTableWidgetItem *item2=new QTableWidgetItem();
                item2->setText(m_pthis->m_SelectionList[i].m_studentz.qsStudentName);
                ui->tableWidget->setItem(nCount,1,item2);
                QTableWidgetItem *item3=new QTableWidgetItem();
                item3->setText(m_pthis->m_SelectionList[i].m_score[j]);
                ui->tableWidget->setItem(nCount,2,item3);
            }
        }

    }
    //如果没有找到，只画表头
    if(nCount == 0)
    {
        ui->tableWidget->setRowCount(nCount + 1);
    }
}
