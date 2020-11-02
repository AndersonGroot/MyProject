#ifndef DELETEWINDOW_H
#define DELETEWINDOW_H

#include <QDialog>
#include <QString>


namespace Ui {
class DeleteWindow;
}


class  MainWindow;
class DeleteWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteWindow(MainWindow *pthis,QWidget *parent = nullptr);
    ~DeleteWindow();
public slots:
   void  deletChooseStu(bool);
   void  deletChooseLes(bool);
   void  deletChooseSelectStu(bool);
   void  deletChooseSelectLesson(bool);

public:
    Ui::DeleteWindow *ui;
    MainWindow *m_pthis;
    QString m_slectStuId;
};

#endif // DELETEWINDOW_H
