#ifndef KARKAS_H
#define KARKAS_H

#include "tcpbot.h"

class Karkas : public TcpBot
{
public:
    Karkas(QObject *parent = 0);

    void Auth();
    Point Turn();
    void TurnResult(const Point& lastHit, int result);
    void EnemyTurnResult(const Point& lastHit, int result);
    void Wait();
    void BattleEnd(bool);
};

#endif // KARKAS_H
