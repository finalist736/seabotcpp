#include <QCoreApplication>
#include <QDebug>
#include <QDateTime>
#include "randombot.h"



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qsrand(QDateTime::currentDateTime().toTime_t());
    RandomBot * bot = new RandomBot();
    bot->tcp->connectToHost("127.0.0.1", 11000);
    bot->tcp->waitForConnected();
    bot->tcp->write("test test test");
    //bot->tcp->waitForBytesWritten();

//    QTcpSocket *s = new QTcpSocket(&a);
//    s->connectToHost("127.0.0.1", 11000);
//    s->waitForConnected();
//    s->write("test test test");
//    s->waitForBytesWritten();
//    s->waitForReadyRead();
//    qDebug() << s->readAll();
//    s->disconnectFromHost();
//    s->deleteLater();

    return a.exec();
}
