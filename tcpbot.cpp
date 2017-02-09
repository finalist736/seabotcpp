#include "tcpbot.h"
#include <QJsonDocument>
#include <QJsonObject>

TcpBot::TcpBot(QObject *parent) : QTcpSocket(parent)
{
    connect(this, SIGNAL(readyRead()), SLOT(readyRead()));
    connect(this, SIGNAL(connected()), SLOT(connected()));
    connect(this, SIGNAL(disconnected()), SLOT(disconnected()));
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)),
            SLOT(error(QAbstractSocket::SocketError)));
}

void TcpBot::Auth()
{
    QJsonObject bvb;
    bvb["bvb"] = TcpBot::Server;
    QJsonDocument doc;
    doc.setObject(bvb);
    QByteArray data = doc.toJson();
    write(data);
}

void TcpBot::readyRead()
{
    qDebug() << "ready read!!! ";

    QByteArray alldata = readAll();

    qDebug() << alldata;
    QJsonParseError parseError;
    auto doc = QJsonDocument::fromJson(alldata, &parseError);
    if (parseError.error != QJsonParseError::NoError)
    {
        qDebug() << parseError.errorString();
        return;
    }

    auto obj = doc.object();

    if (obj.contains("auth")) {
        QJsonValue auth = obj["auth"];
        QJsonObject authResponse = auth.toObject();
        if (authResponse["ok"].toBool() == false) {
            qDebug() << "Auth error: " << authResponse["error"].toString();
            return;
        } else {
            Auth();
        }
    } else if (obj.contains("bvb")) {
        QJsonValue bvb = obj["bvb"];
        QJsonObject bvbResponse = bvb.toObject();
        if (bvbResponse.contains("wait")) {
            Wait();
        } else {
            // bvb ready to battle, lets prepare
        }
    }


    auto a = this->Turn();

    qDebug() << "random hit: " << a.x << a.y;
}

void TcpBot::connected()
{
    QJsonObject auth;
    auth["Auth"] = QJsonValue(mAuthKey);
    QJsonDocument doc;
    doc.setObject(auth);

    QByteArray data = doc.toJson();
    write(data);
}

void TcpBot::disconnected()
{
    qDebug() << "socket disconnected";
}

void TcpBot::error(QAbstractSocket::SocketError e)
{
    qDebug() << e;
}
