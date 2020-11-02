#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_deletewindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置正则表达式，学生id可接受字母，数字类型的数据，但不超过11个
    QRegExp regExpID("[A-Za-z0-9]{1,11}");
    ui->txtStuId->setValidator(new QRegExpValidator(regExpID, this));
    //设置正则表达式，课程id可接受字母，数字类型的数据，但不超过11个
    ui->txtLessonId->setValidator(new QRegExpValidator(regExpID, this));
    //学生姓名长度不超过8
    ui->txtStuName->setMaxLength(8);
    //课程名长度不超过16
    ui->txtLessonName->setMaxLength(16);

    //100个基础课程
    //显示课程菜单,并将课程加入链表
    CMyLesson lesson;
    for(int i = 0;i < 100;i++)
    {
       //将课程信息存进类
       lesson.qsLessonName = Cou[0][i];
       lesson.qsLessonId = QString("%1").arg(i + 1);
       ui->cmb_lesid->addItem(lesson.qsLessonId);
       //类入栈
       m_LessonList.push_back(lesson);
    }

    //1000个基础学生
    CMyStudent stu;
    for(int i = 0;i < 1000;i++)
    {
        //将学生信息存进类
        stu.qsStudentName = Stu[0][i];
        stu.qsStudentId = QString("%1").arg(i + 1);
        //学生类入栈
        m_StudentList.push_back(stu);
        ui->cmb_stuid->addItem(stu.qsStudentId);
        CMySelection select;
        CMyLesson sub;
        select.m_studentz = stu;
        //10000条选课记录
        for(int j = 0;j < 10;j++)
        {
            sub.qsLessonName = Cou[0][j];
            sub.qsLessonId = QString("%1").arg(j + 1);
            select.m_lesson.push_back(sub);
            select.m_score.push_back(QString("%1").arg((10-j)*10));
        }
        m_SelectionList.push_back(select);
    }
    //显示分数选项
    for(int i=100;i>=0;i--)
    {
        QString qs = QString("%1").arg(i);
        ui->cmbScore->addItem(qs);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

//删除学生或课程后，删除下拉菜单相应的选项
void MainWindow::deletStuCmb(int pos)
{
    ui->cmb_stuid->removeItem(pos);
}

void MainWindow::deletLesCmb(int pos)
{
    ui->cmb_lesid->removeItem(pos);
}



//添加学生信息
void MainWindow::addStudentInfo(bool)
{
  CMyStudent student;
    //接受信息
    student.qsStudentId = ui->txtStuId->text();
    student.qsStudentName = ui->txtStuName->text();
    //判断信息
    if(student.qsStudentId.isEmpty())
    {
        //弹框警告
        QMessageBox::about(this,"error","学生Id为空");
        return;
    }
    else if(student.qsStudentName.isEmpty())
    {
        //弹框警告
          QMessageBox::about(this,"error","学生姓名为空");
        return;
    }
    //判断对应的ID只能有一个名字
    if(!m_StudentList.isEmpty())
    {
        for(int i = 0;i < m_StudentList.size();i++)
        {
            if(m_StudentList[i].qsStudentId == student.qsStudentId )
            {
                //弹窗警告，ID重复了
                QMessageBox::about(this,"error","学生ID重复");
                return ;
            }
        }
    }

    //入链表
    m_StudentList.push_back(student);
    QMessageBox::about(this,"Success","学生信息添加成功");
   //显示在复选框
    ui->cmb_stuid->addItem(student.qsStudentId);
//    //显示在删除界面
//    m_del->ui->del_cmb_stuId->addItem(student.qsStudentId);
//    m_del->ui->del_cmb_seleStuId->addItem(student.qsStudentId);
//    m_del->ui->del_cmb_stuName->addItem(student.qsStudentName);
}


//添加课程信息
void MainWindow::addLessonInfo(bool)
{
    CMyLesson lesson;
      //接受信息
    lesson.qsLessonId = ui->txtLessonId->text();
    lesson.qsLessonName = ui->txtLessonName->text();

      //判断信息
      if(lesson.qsLessonId.isEmpty())
      {
          //弹框警告
          QMessageBox::about(this,"error","课程ID为空");
          return;
      }
      else if(lesson.qsLessonName.isEmpty())
      {
          //弹框警告
          QMessageBox::about(this,"error","课程名为空");
          return;
      }
      //判断对应的ID只能有一个名字
      if(!m_LessonList.isEmpty())
      {
          for(int i=0;i<m_LessonList.size();i++)
          {
              if(m_LessonList[i].qsLessonId == lesson.qsLessonId )
              {
                  //弹窗警告，ID重复了
                  QMessageBox::about(this,"error","课程ID重复");
                  return ;
              }
              if(m_LessonList[i].qsLessonName == lesson.qsLessonName)
              {
                  //弹窗警告，课程名重复了
                  QMessageBox::about(this,"error","课程名重复");
                  return ;
              }
          }
      }

      //入链表
      m_LessonList.push_back(lesson);
      QMessageBox::about(this,"Success","课程信息添加成功");
     //显示在复选框
      ui->cmb_lesid->addItem( lesson.qsLessonId);
//      //显示在删除界面
//      m_del->ui->del_cmb_lesId->addItem(lesson.qsLessonId);
//      m_del->ui->del_cmb_seleLesId->addItem(lesson.qsLessonId);
//      m_del->ui->del_cmb_lesName->addItem(lesson.qsLessonName);
}


//添加选课信息
void MainWindow::addSelectionInfo(bool)
{
    CMySelection select;
    CMyLesson les;
//    CMyStudent student;
    //接受信息
    QString score=ui->cmbScore->currentText();
    QString lesson=ui->cmb_lesid->currentText();
    QString stuid=ui->cmb_stuid->currentText();
    QString stuName;
    QString lessonName;

    //判断信息
    //首先判断有没有选中值
    if(score==nullptr||lesson==nullptr||stuid==nullptr)
    {
        //弹窗警告，有的项没选
        QMessageBox::about(this,"error","请勿漏选");
        return ;
    }
    //判断
    if(!m_SelectionList.isEmpty())
    {
        for(int k=0;k<m_StudentList.size();k++)
        {
            //判断学生链表有没有这个学生
            if(m_StudentList[k].qsStudentId==stuid)
            {
                for(int i=0;i<m_SelectionList.size();i++)
                {
                    //如果有这个学生
                    if(m_SelectionList[i].m_studentz.qsStudentId == stuid)
                    {
                        //就要判断这个学生有没有选这个课
                        for(int j=0;j<m_SelectionList[i].m_lesson.size();j++)
                        {
                          if(m_SelectionList[i].m_lesson[j].qsLessonId ==lesson)
                            {
                              //报错，不能重复添加同一门课程
                              QMessageBox::information(this, "error", "课程重复添加");
                              return;
                            }
                        }

                        //根据Id找名字
                        for(int i=0;i<m_StudentList.size();i++)
                        {
                            if(m_StudentList[i].qsStudentId==stuid)
                            {
                                stuName=m_StudentList[i].qsStudentName;
                            }
                        }
                        for(int i=0;i<m_LessonList.size();i++)
                        {
                            if(m_LessonList[i].qsLessonId==lesson)
                            {
                                lessonName=m_LessonList[i].qsLessonName;
                            }
                        }
                        //课程信息记录
                        les.qsLessonId = lesson;
                        les.qsLessonName = lessonName;


                        m_SelectionList[i].m_lesson.push_back(les);
                        //分数入链表
                        select.m_score.push_back(score);
                        m_SelectionList[i].m_score.push_back(score);
                        //弹框提示，信息增加成功
                        QMessageBox::about(this,"Success","学生信息增加成功");
                        return;
                     }
                }
            }
         }

 }

    //根据Id找名字
    for(int i=0;i<m_StudentList.size();i++)
    {
        if(m_StudentList[i].qsStudentId==stuid)
        {
            stuName=m_StudentList[i].qsStudentName;
        }
    }
    for(int i=0;i<m_LessonList.size();i++)
    {
        if(m_LessonList[i].qsLessonId==lesson)
        {
            lessonName=m_LessonList[i].qsLessonName;
        }
    }

        //分数入链表
        select.m_score.push_back(score);
        //学生信息记录
        select.m_studentz.qsStudentId=stuid;
        select.m_studentz.qsStudentName=stuName;

        //课程信息记录
        les.qsLessonId = lesson;
        les.qsLessonName = lessonName;

        //课程信息入链表
        select.m_lesson.push_back(les);
        //选课记录入链表
        m_SelectionList.push_back(select);

        //弹框提示，信息增加成功
        QMessageBox::about(this,"Success","学生信息增加成功");
        return;

}

void MainWindow::findWindow(bool)
{
    m_find=new CMyFindWindow(this);
    m_find  ->exec();
}

void MainWindow::deletWindow(bool)
{
    m_del=new  DeleteWindow(this);
    m_del->exec();

}

void MainWindow::modifyWindow(bool)
{
    m_modify=new ModifyWindow(this);
    m_modify->exec();
}
