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
public slots:
    void showString(QString str);
    void silenceSlot();
};
QString str2qstr(const string str);
#endif // MAINWINDOW_H
