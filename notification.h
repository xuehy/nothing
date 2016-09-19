#ifndef NOTIFICATION_H
#define NOTIFICATION_H
#include <qthread.h>
#include <qdatetime.h>
#include <string>
using namespace std;
class Notification : public QThread
{

    Q_OBJECT
private:
    QString str;
    bool emitted;
    bool visible;
protected:
    void run();
public:
    Notification(QObject *parent=0);
    ~Notification();
signals:
    void UpdateSignal(QString str);
    void silenceSignal();
};


#endif // NOTIFICATION_H
