#ifndef MODIFYWINDOW_H
#define MODIFYWINDOW_H

#include <QDialog>

namespace Ui {
class ModifyWindow;
}

//声明
class MainWindow;

class ModifyWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ModifyWindow( MainWindow *pthis,QWidget *parent = nullptr);
    ~ModifyWindow();

public slots:
 void clickedModifyBtn(bool);
 void clickedModifyBtn2(bool);
private:
    Ui::ModifyWindow *ui;
    MainWindow *m_pthis;  //设置this指针的成员变量
};

#endif // MODIFYWINDOW_H
