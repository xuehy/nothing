#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qsystemtrayicon.h>
#include <qthread.h>
#include <qdatetime.h>
#include "notification.h"
#include <qpixmap.h>
#include <qbitmap.h>
#include <qgridlayout.h>
#include <qtoolbutton.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <QMouseEvent>
#include <QFontDatabase>
namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason);
private:
    Ui::MainWindow *ui;
    Notification *notify;
    QSystemTrayIcon *mSysTrayIcon;
    QToolButton *closeButton;
    QLabel *textBrowser;
    QPushButton *pushButton;

    QPoint move_point;   //鼠标按下位置
    bool mouse_press;    //鼠标是否按下的标识
public slots:
    void showString(QString str);
    void silenceSlot();
protected:
    //重载基类的鼠标按下事件处理函数
       virtual void mousePressEvent(QMouseEvent *event);
       //重载基类的鼠标释放事件处理函数
       virtual void mouseReleaseEvent(QMouseEvent *event);
       //重载基类的鼠标移动事件处理函数
       virtual void mouseMoveEvent(QMouseEvent *event);

};
QString str2qstr(const string str);
#endif // MAINWINDOW_H
