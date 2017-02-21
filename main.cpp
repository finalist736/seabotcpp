#include <QCoreApplication>
#include <QDebug>
#include <QDateTime>
#include <QThread>
#include "linerbot.h"
#include "randombot.h"
#include "winscounter.h"
#include "qeventdispatcher_epoll.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setEventDispatcher(new QEventDispatcherEpoll);

    QCoreApplication a(argc, argv);

    qsrand(QDateTime::currentDateTime().toTime_t());

    WinsCounter *wc = new WinsCounter(&a);


    for (int i=0; i<1000; i++)
    {
        RandomBot * rbot = new RandomBot();
        QMetaObject::Connection c = QObject::connect(rbot, SIGNAL(Win(QString)), wc, SLOT(Win(QString)));
        rbot->connectToHost("127.0.0.1", 11000);


        LinerBot * bot = new LinerBot(&a);
        QObject::connect(bot, SIGNAL(Win(QString)), wc, SLOT(Win(QString)));
        bot->connectToHost("127.0.0.1", 11000);

        //rbot->waitForDisconnected();
        //bot->waitForDisconnected();
        QThread::msleep(10);

        //QObject::disconnect()

        //rbot->deleteLater();
        //bot->deleteLater();
    }



    return a.exec();
}
