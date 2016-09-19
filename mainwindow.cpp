#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    notify(new Notification)
{
    setFixedSize(600,600);
    //setMask((new QPixmap("cat.png"))->mask());
    QPalette* palette = new QPalette();
        palette->setBrush(QPalette::Background,QBrush(QPixmap("cat.jpg")));
        setPalette(*palette);
        //setWindowFlags(Qt::FramelessWindowHint);
    QWidget *centralWidget = new QWidget(this);
    QGridLayout *layout = new QGridLayout();

    centralWidget->setLayout(layout);

    connect(notify, SIGNAL(UpdateSignal(QString)),
            this, SLOT(showString(QString)));
    notify -> start();

    mSysTrayIcon = new QSystemTrayIcon(this);
    QIcon icon = QIcon("image/cup.png");
    mSysTrayIcon->setIcon(icon);
    mSysTrayIcon->setToolTip(QObject::trUtf8("默默等待提醒你吃饭哦~"));
    connect(mSysTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));

    connect(notify, SIGNAL(silenceSignal()), this, SLOT(silenceSlot()));
    //ui->pushButton->setMask((new QPixmap("craw.png"))->mask());
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete notify;
    delete mSysTrayIcon;
}

void MainWindow::on_pushButton_clicked()
{
    ui->textBrowser->clear();
    //隐藏程序主窗口
    this->hide();
    //在系统托盘显示此对象
    mSysTrayIcon->show();
    mSysTrayIcon->showMessage(QString(str2qstr(string("温馨提示"))),QString(str2qstr(string("我还在这里哦～"))),QSystemTrayIcon::Information,5000);
}


void MainWindow::activatedSysTrayIcon(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason){
    case QSystemTrayIcon::Trigger:
        //单击托盘图标
        this->show();
        mSysTrayIcon -> hide();
        break;
    case QSystemTrayIcon::DoubleClick:
        //双击托盘图标
        //双击后显示主程序窗口
        this->show();
        mSysTrayIcon -> hide();
        break;
    default:
        break;
    }
}

void MainWindow::showString(QString str)
{
    if (!(this->isVisible()))
    {
        this -> show();
        mSysTrayIcon->hide();
    }
    ui->textBrowser->setText(str);
}

void MainWindow::silenceSlot()
{
    ui->textBrowser->setText(QString(str2qstr(string("等待提醒吃饭"))));
    if(this->isVisible())
    {
        this -> hide();
        mSysTrayIcon -> show();
    }
}
