#ifndef TCPBOT_H
#define TCPBOT_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>

const int N = 10;

struct Point {
    int x,y;
};

class TcpBot : public QTcpSocket
{
    Q_OBJECT
private:
    int msgSize;
    int myID;
    QDataStream m_stream;
protected:
    enum ServerShipsPlace {
        Server = 0,
        Bot
    };
    int mOpponentID;
    QString mAuthKey;
    QString mOpponentName;
    int mPole[N][N];
    Point lastTurn;

    inline void SetMyID(int id) {
        myID = id;
    }
    int MyID() const {
        return myID;
    }


public:
    explicit TcpBot(QObject *parent = 0);

    void Send(const QByteArray& result);
    void ParseProtocol(const QJsonDocument& doc);


    virtual void Auth();
    virtual Point Turn() = 0;
    virtual void TurnResult(const Point& lastHit, int result) = 0;
    virtual void EnemyTurnResult(const Point& lastHit, int result) = 0;
    virtual void Wait() = 0;
    virtual void BattleEnd(bool winner) = 0;

signals:

public slots:
    void readyRead();
    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError);


};

#endif // TCPBOT_H
