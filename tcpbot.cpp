#include "tcpbot.h"

TcpBot::TcpBot(QObject *parent) : QObject(parent)
{
    tcp = new QTcpSocket(this);
    connect(tcp, SIGNAL(readyRead()), SLOT(readyRead()));
}

void TcpBot::readyRead()
{
    qDebug() << "super ready read!!! " << tcp->readAll();
    auto a = this->Turn();

    qDebug() << "random hit: " << a.x << a.y;
}
