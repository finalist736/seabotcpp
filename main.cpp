#include <QCoreApplication>
#include <QDebug>
#include <QDateTime>
#include <QThread>
#include "linerbot.h"
#include "randombot.h"
#include "winscounter.h"
#ifdef Q_OS_LINUX
#include "qeventdispatcher_epoll.h"
#endif

int main(int argc, char *argv[])
{
#ifdef Q_OS_LINUX
    QCoreApplication::setEventDispatcher(new QEventDispatcherEpoll);
#endif

    QCoreApplication a(argc, argv);

    qsrand(QDateTime::currentDateTime().toTime_t());

    //WinsCounter *wc = new WinsCounter(&a);


    RandomBot * rbot = new RandomBot();
    //QMetaObject::Connection c = QObject::connect(rbot, SIGNAL(Win(QString)), wc, SLOT(Win(QString)));
    rbot->connectToHost("88.99.171.92", 11000);


    //LinerBot * bot = new LinerBot(&a);
    //QObject::connect(bot, SIGNAL(Win(QString)), wc, SLOT(Win(QString)));
    //bot->connectToHost("127.0.0.1", 11000);

//    for (int i=0; i<100; i++)
//    {
//        RandomBot * rbot = new RandomBot();
//        QMetaObject::Connection c = QObject::connect(rbot, SIGNAL(Win(QString)), wc, SLOT(Win(QString)));
//        rbot->connectToHost("88.99.171.92", 11000);


//        LinerBot * bot = new LinerBot(&a);
//        QObject::connect(bot, SIGNAL(Win(QString)), wc, SLOT(Win(QString)));
//        bot->connectToHost("88.99.171.92", 11000);

//        //rbot->waitForDisconnected();
//        //bot->waitForDisconnected();
//        QThread::msleep(10);

//        //QObject::disconnect()

//        //rbot->deleteLater();
//        //bot->deleteLater();
//    }



    return a.exec();
}
