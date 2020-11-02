#include "deletewindow.h"
#include "ui_deletewindow.h"
#include "mainwindow.h"
#include <QMessageBox>


DeleteWindow::DeleteWindow(MainWindow *pthis,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteWindow)
{
    ui->setupUi(this);
    m_pthis =pthis ;

    //显示学生
    for(int i=0;i<m_pthis->m_StudentList.size();i++)
    {
        QString tempId=m_pthis->m_StudentList[i].qsStudentId;
        QString tempName=m_pthis->m_StudentList[i].qsStudentName;
        ui->del_cmb_stuId->addItem(tempId);
       // ui->del_cmb_seleStuId->addItem(tempId);
        //ui->del_cmb_stuName->addItem(tempName);
    }

    //显示课程
    for(int i=0;i<m_pthis->m_LessonList.size();i++)
    {
        QString tempId=m_pthis->m_LessonList[i].qsLessonId;
        QString tempName=m_pthis->m_LessonList[i].qsLessonName;
        ui->del_cmb_lesId->addItem(tempId);
       // ui->del_cmb_stuName->addItem(tempName);
    }

    //注释原因：  每个学生得选课不一样，选课里面得课程ID不能预先显示
    //显示选课
    for(int i=0;i<m_pthis->m_SelectionList.size();i++)
    {
        QString tempId=m_pthis->m_SelectionList[i].m_studentz.qsStudentId;
        ui->del_cmb_seleStuId->addItem(tempId);
    }

}



DeleteWindow::~DeleteWindow()
{
    delete ui;
}

//删除学生
void DeleteWindow::deletChooseStu(bool)
{
//1、接收用户选择得学生
    QString tempStuId=ui->del_cmb_stuId->currentText();
    int pos=ui->del_cmb_stuId->currentIndex();
  //遍历学生链表删除学生
    for(int i=0;i<m_pthis->m_StudentList.size();i++)
    {
        if(m_pthis->m_StudentList[i].qsStudentId == tempStuId)
        {
            m_pthis->m_StudentList.removeAt(i);
        }
    }

    //遍历删除选课链表
    for(int i=0;i<m_pthis->m_SelectionList.size();i++)
    {
        if(m_pthis->m_SelectionList[i].m_studentz.qsStudentId == tempStuId)
        {
            m_pthis->m_SelectionList.removeAt(i);
        }
    }

    //删除下拉菜单
    ui->del_cmb_stuId->removeItem(pos);
    //删除主界面 的选项
    m_pthis->deletStuCmb(pos);


//提示
   QMessageBox::about(this,"提示","学生信息删除成功");
   return ;
}

//删除课程
void DeleteWindow::deletChooseLes(bool)
{

    //1、接收用户选择得课程
        QString tempLesId=ui->del_cmb_lesId->currentText();
        int pos=ui->del_cmb_lesId->currentIndex();
      //遍历课程链表删除课程
        for(int i=0;i<m_pthis->m_LessonList.size();i++)
        {
            if(m_pthis->m_LessonList[i].qsLessonId == tempLesId)
            {
                m_pthis->m_LessonList.removeAt(i);
            }
        }

        //遍历选课链表
        for(int i=0;i<m_pthis->m_SelectionList.size();i++)
        {
            //遍历课程链表
            for(int j=0;j<m_pthis->m_SelectionList[i].m_lesson.size();j++)
            {
                //删除该课程
                if(m_pthis->m_SelectionList[i].m_lesson[j].qsLessonId == tempLesId )
                {
                    m_pthis->m_SelectionList[i].m_lesson.removeAt(j);
                    break;
                }
            }
        }

        //删除下拉菜单
        ui->del_cmb_lesId->removeItem(pos);

        //删除主界面 的选项
        m_pthis->deletLesCmb(pos);

        //提示
        QMessageBox::about(this,"提示","课程信息删除成功");
        return ;
}


//删除选课信息

void DeleteWindow::deletChooseSelectStu(bool)
{
    //1、接收用户选择得学生
    m_slectStuId =ui->del_cmb_seleStuId->currentText();
    //2、遍历链表找到对应的额

    for(int i=0;i<m_pthis->m_SelectionList.size();i++)
    {
        //找到对应学生得下标
        if(m_pthis->m_SelectionList[i].m_studentz.qsStudentId == m_slectStuId)
        {
             //3、根据用户选择得学生将 学生得课程列到  cmb里面
            for(int j=0;j<m_pthis->m_SelectionList[i].m_lesson.size();j++)
            {
                QString tempLessonId =m_pthis->m_SelectionList[i].m_lesson[j].qsLessonId;
                ui->del_cmb_seleLesId->addItem(tempLessonId);
            }
        }
    }

}

void DeleteWindow::deletChooseSelectLesson(bool)
{


//获取用户选择得Id
    QString tempLesssonId = ui->del_cmb_seleLesId->currentText();
    if(tempLesssonId == nullptr)
    {
        QMessageBox::about(this,"提示","请先确定学生");
        return;
    }
    int pos=ui->del_cmb_seleLesId->currentIndex();
 //遍历链表，删除
    for(int i=0;i<m_pthis->m_SelectionList.size();i++)
    {
        //找到对应ID得下标
        if(m_pthis->m_SelectionList[i].m_studentz.qsStudentId == m_slectStuId)
        {
             //遍历
            for(int j=0;j<m_pthis->m_SelectionList[i].m_lesson.size();j++)
            {
                //找到对应的课程
                if(m_pthis->m_SelectionList[i].m_lesson[j].qsLessonId==tempLesssonId)
                {
                    //删除   节点下标对应得，分数和课程
                    m_pthis->m_SelectionList[i].m_lesson.removeAt(j);
                    m_pthis->m_SelectionList[i].m_score.removeAt(j);
                }

            }
        }
    }
    //删除选课记录的下拉菜单选项
    ui->del_cmb_seleLesId->removeItem(pos);

    //提示
    QMessageBox::about(this,"提示","选课信息删除成功");
    return ;

}
