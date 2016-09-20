#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    notify(new Notification)
{
    QFontDatabase::addApplicationFont(":/f.ttf");
    textBrowser = new QLabel(this);
    textBrowser->setGeometry(660,410,200,200);
    textBrowser->setWordWrap(true);
    textBrowser->setAlignment(Qt::AlignTop);
    textBrowser->setText(QObject::trUtf8("默默等待提醒你吃饭哦~"));
    textBrowser->setFont(QFont("f", 20));
    pushButton = new QPushButton(this);
    pushButton->setGeometry(800,700,120,100);
    pushButton->setMask((new QPixmap(":/craw1.png"))->mask());

    // buttons
    //获取最小化、关闭按钮图标
     closeButton = new QToolButton(this);
     QPixmap closePix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
     //设置最小化、关闭按钮图标
     closeButton->setIcon(closePix);
     //设置最小化、关闭按钮在界面的位置
     closeButton->setGeometry(900,350,30,30);
     closeButton->setStyleSheet("background-color:transparent;");
     closeButton->setToolTip(tr("关闭"));
     connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

     // 设置窗口形状和图案
    setFixedSize(1000,957);
    setMask((new QPixmap(":/m.png"))->mask());
    QPalette* palette = new QPalette();
    palette->setBrush(QPalette::Background,QBrush(QPixmap(":/m.png")));
    setPalette(*palette);

    setWindowFlags(Qt::FramelessWindowHint| Qt::Dialog );
    QWidget *centralWidget = new QWidget(this);
    QGridLayout *layout = new QGridLayout();

    centralWidget->setLayout(layout);

    connect(notify, SIGNAL(UpdateSignal(QString)),
            this, SLOT(showString(QString)));
    notify -> start();

    mSysTrayIcon = new QSystemTrayIcon(this);
    QIcon icon = QIcon(":/cup.png");
    mSysTrayIcon->setIcon(icon);
    mSysTrayIcon->setToolTip(QObject::trUtf8("默默等待提醒你吃饭哦~"));
    connect(mSysTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(activatedSysTrayIcon(QSystemTrayIcon::ActivationReason)));
    connect(pushButton, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_clicked()));
    connect(notify, SIGNAL(silenceSignal()), this, SLOT(silenceSlot()));
    //ui->pushButton->setMask((new QPixmap("craw1.png"))->mask());
    //ui->setupUi(this);

}
//重载基类的鼠标按下事件处理函数
void MainWindow:: mousePressEvent(QMouseEvent *event)
{
    //只能是鼠标左键移动
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
    }
    /*
     * 窗口移动距离
     * globalPose(), 以桌面左上角为原点，绝对坐标
     * pos(), 窗体左上角（不含边框）的坐标，只要鼠标在窗体内，且窗体不动，坐标不变
     */
    move_point = event->globalPos() - pos();
}
//重载基类的鼠标释放事件处理函数
void MainWindow:: mouseReleaseEvent(QMouseEvent *event)
{
    mouse_press = false;
}

//重载基类的鼠标移动事件处理函数
void MainWindow:: mouseMoveEvent(QMouseEvent *event)
{
    //移动窗口
    if(mouse_press)
    {
        /*
         *  event->globalPos() - move_point
         * =event->globalPos() - (event->globalPos0() - pos0())
         * =pos() + (event->globalPos() - event->globalPos0())
         */
         move(event->globalPos() - move_point);
    }
}
MainWindow::~MainWindow()
{
    delete ui;
    delete notify;
    delete mSysTrayIcon;
    delete textBrowser;
    delete closeButton;
}

void MainWindow::on_pushButton_clicked()
{
    textBrowser->clear();
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
    textBrowser->setText(str);
}

void MainWindow::silenceSlot()
{
    textBrowser->setText(QString(str2qstr(string("等待提醒吃饭"))));
    if(this->isVisible())
    {
        this -> hide();
        mSysTrayIcon -> show();
       textBrowser->setText(QString(str2qstr(string("饿啦？"))));
    }
}
