#ifndef CMYFINDWINDOW_H
#define CMYFINDWINDOW_H

#include <QDialog>
#include <QList>
#include <QString>


namespace Ui {
class CMyFindWindow;
}

class  MainWindow;

class CMyFindWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CMyFindWindow(MainWindow *pthis,QWidget *parent = nullptr);
    ~CMyFindWindow();

public slots:
    void stuInfoFindSlots(bool);
    void stuIdFindSlots(bool);
    void subInfoFindSlots(bool);
    void subIdFindSlots(bool);
    void selSubInfoFindSlots(bool);
    void selStuInfoFindSlots(bool);
    void selSubFindSlots(bool);

private:
    Ui::CMyFindWindow *ui;
    MainWindow *m_pthis; //保存主窗口的this指针
    QString m_text; //保存文本框中的信息
    QString m_subId;
};

#endif // CMYFINDWINDOW_H
