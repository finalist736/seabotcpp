#ifndef TCPBOT_H
#define TCPBOT_H

#include <QObject>
#include <QTcpSocket>


struct Point {
    int x,y;
};

class TcpBot : public QTcpSocket
{
protected:
    enum ServerShipsPlace {
        Server = 0,
        Bot
    };

    QString mAuthKey;
    Q_OBJECT
public:
    explicit TcpBot(QObject *parent = 0);
    virtual void Auth();
    virtual Point Turn() = 0;
    virtual void TurnResult(const Point& lastHit, int result) = 0;
    virtual void EnemyTurnResult(const Point& lastHit, int result) = 0;
    virtual void Wait() = 0;

signals:

public slots:
    void readyRead();
    void connected();
    void disconnected();
    void error(QAbstractSocket::SocketError);


};

#endif // TCPBOT_H
