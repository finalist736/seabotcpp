#include "tcpbot.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <iostream>

TcpBot::TcpBot(QObject *parent) :
    QTcpSocket(parent),
    mbWinner(false),
    msgSize(0),
    m_stream(this)
{
    connect(this, SIGNAL(readyRead()), SLOT(readyRead()));
    connect(this, SIGNAL(connected()), SLOT(connected()));
    connect(this, SIGNAL(disconnected()), SLOT(disconnected()));
    connect(this, SIGNAL(error(QAbstractSocket::SocketError)),
            SLOT(error(QAbstractSocket::SocketError)));
}

void TcpBot::Send(const QByteArray &result)
{
    //qDebug() << "<=" << result;
    //add 4 bytes of header
    QByteArray tosend;
    int size = result.length();
    tosend.reserve(size + 4);

    tosend.append(static_cast<char>(((size >> 24) & 0xFF)));
    tosend.append(static_cast<char>(((size >> 16) & 0xFF)));
    tosend.append(static_cast<char>(((size >> 8) & 0xFF)));
    tosend.append(static_cast<char>((size & 0xFF)));

    tosend.append(result);

    write(tosend);
    waitForBytesWritten();
}

void TcpBot::ParseProtocol(const QJsonDocument &doc)
{
    auto obj = doc.object();

    if (obj.contains("auth")) {
        QJsonValue auth = obj["auth"];
        QJsonObject authResponse = auth.toObject();
        if (authResponse["ok"].toBool() == false) {
            qDebug() << "Auth error: " << authResponse["error"].toString();
            return;
        } else {
            SetMyID(authResponse["id"].toInt());
            Auth();
        }
    } else if (obj.contains("bvb")) {
        QJsonValue bvb = obj["bvb"];
        QJsonObject bvbResponse = bvb.toObject();
        if (bvbResponse.contains("wait")) {
            Wait();
        } else {
            if (bvbResponse.contains("id"))
            {
                mOpponentID = bvbResponse["id"].toInt();
            }
            if (bvbResponse.contains("name"))
            {
                mOpponentName = bvbResponse["name"].toString();
            }
            if (bvbResponse.contains("ships"))
            {
                QJsonArray a = bvbResponse["ships"].toArray();
                int i = 0, j = 0;
                for (auto it = a.begin(); it!=a.end(); ++it)
                {
                    QJsonValue v(*it);
                    mPole[i][j] = v.toInt();
                    j++;
                    if (j == 10){
                        j = 0;
                        i++;
                    }
                }
                //qDebug() << mPole;
//                for (i=0;i<10;i++)
//                {
//                    for (j=0;j<10;j++)
//                    {
//                        std::cout << mPole[i][j];
//                    }
//                    std::cout << "\n";
//                }
            }
            BattleStart(mOpponentID, mOpponentName);
        }
    } else if (obj.contains("turn")) {
        QJsonObject turnObject = obj["turn"].toObject();

        if (turnObject.contains("result")) {
            TurnResult(lastTurn, turnObject["result"].toInt());
        } else if (turnObject.contains("id")) {
            if (MyID() == turnObject["id"].toInt()) {
                lastTurn = Turn();
                QJsonArray shotArray;
                shotArray.append(lastTurn.y);
                shotArray.append(lastTurn.x);
                QJsonObject shotObject;
                shotObject["shot"] = shotArray;
                QJsonObject shotObjectTurn;
                shotObjectTurn["turn"] = shotObject;
                QJsonDocument doc;
                doc.setObject(shotObjectTurn);
                QByteArray data = doc.toJson();
                Send(data);
            }
        } else if (turnObject.contains("opponent")) {
            QJsonObject opponent = turnObject["opponent"].toObject();
            QJsonArray shot = opponent["shot"].toArray();
            Point shotPoint = Point{shot[1].toInt(),shot[0].toInt()};
            EnemyTurnResult(shotPoint, opponent["result"].toInt());
        }
    } else if (obj.contains("end")) {
        QJsonObject end = obj["end"].toObject();
        BattleEnd(end["winner"].toInt() == MyID());
    } else if (obj.contains("error")) {
        qDebug() << obj["error"].toObject();
    }
}

void TcpBot::Auth()
{
    QJsonObject bvb;
    QJsonObject placeShips;
    QJsonArray ships;
    ships.append(0);
    ships.append(0);
    ships.append(0);
    ships.append(0);
    placeShips["place"] = TcpBot::Server;
    placeShips["ships"] = ships;
    bvb["bvb"] = placeShips;
    QJsonDocument doc;
    doc.setObject(bvb);
    QByteArray data = doc.toJson();
    Send(data);
}



void TcpBot::readyRead()
{
    //qDebug() << "ready read!!! ";

    if (state() == ConnectedState)
    {
        if (msgSize == 0 && bytesAvailable() < 4) {
            return;
        }
        if (msgSize == 0) {
            m_stream >> msgSize;
        }

        if (bytesAvailable() < msgSize) {
            return;
        }

        QByteArray alldata;
        unsigned char sym = 0;
        while (msgSize > 0)
        {
            m_stream >> sym;
            alldata.append(sym);
            msgSize--;
        }
        msgSize = 0;

        // *****
        // parse data
        //qDebug() << alldata;
        QJsonParseError parseError;
        auto doc = QJsonDocument::fromJson(alldata, &parseError);
        if (parseError.error != QJsonParseError::NoError)
        {
            qDebug() << parseError.errorString();
            return;
        }
        ParseProtocol(doc);
        // *****
        if (bytesAvailable() > 0)
        {
            readyRead();
        }
    }
}

void TcpBot::connected()
{
    QJsonObject auth;
    auth["Auth"] = QJsonValue(mAuthKey);
    QJsonDocument doc;
    doc.setObject(auth);

    QByteArray data = doc.toJson();
    Send(data);
}

void TcpBot::disconnected()
{
    qDebug() << "socket disconnected";

}

void TcpBot::error(QAbstractSocket::SocketError e)
{
    Q_UNUSED(e);
    deleteLater();
    //qDebug() << e;
}
