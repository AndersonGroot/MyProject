#ifndef CMYSTUDENT_H
#define CMYSTUDENT_H
#include <QString>
#include <QList>

//学生类
class CMyStudent
{
public:
  QString qsStudentId;   //学生ID
  QString qsStudentName; //学生姓名
};

//课程类
class CMyLesson
{
public:
  QString qsLessonId;   //课程ID
  QString qsLessonName; //课程名
};

//选课类
class CMySelection
{
public:
  CMyStudent m_studentz;    //学生类
  QList<CMyLesson> m_lesson;//课程类链表
  QList<QString> m_score;   //分数链表
};

#endif // CMYSTUDENT_H
