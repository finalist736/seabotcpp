#ifndef TCPBOT_H
#define TCPBOT_H

#include <QObject>
#include <QTcpSocket>


struct Point {
    int x,y;
};
class TcpBot : public QObject
{
    Q_OBJECT
public:
    QTcpSocket *tcp;

public:
    explicit TcpBot(QObject *parent = 0);
    virtual Point Turn() = 0;
    virtual void TurnResult(const Point& lastHit, int result) = 0;

signals:

public slots:
    void readyRead();


};

#endif // TCPBOT_H
