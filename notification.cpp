#include "notification.h"
QString str2qstr(const string str)
{
    return QString::fromLocal8Bit(str.data());
}
Notification::Notification(QObject *parent)
{
    str = "";
    emitted = false;
}

void Notification::run()
{
    while(1)
    {
        QDateTime time = QDateTime::currentDateTime();
        str = time.toString("yyyy-MM-dd hh:mm:ss ddd");
        QTime current_time = QTime::currentTime();
        int hour = current_time.hour();
        int minute = current_time.minute();
        if(hour == 17 && minute >=0 && minute < 1 && !emitted)
        {
            str = QString(str2qstr(string("快去吃晚饭吧！吃完了才能更聪明！")));
            emitted = true;
            emit UpdateSignal(str);
        }
        else if(emitted && hour == 17 && minute >= 1)
        {
            emitted = false;
            emit silenceSignal();
        }
        else if(hour == 11 && minute >= 30 && minute < 31 && !emitted)
        {
            str = QString(str2qstr(string("快去吃午饭吧！吃完了才能更聪明！")));
            emitted = true;
            emit UpdateSignal(str);
        }
        else if(emitted && hour == 11 && minute >= 31)
        {
            emitted = false;
        }

        sleep(5);
    }
}

Notification::~Notification()
{

}
