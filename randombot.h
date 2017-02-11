#ifndef RANDOMBOT_H
#define RANDOMBOT_H

#include "tcpbot.h"

class RandomBot : public TcpBot
{
private:
    QList<Point> arr;
public:
    RandomBot();
    Point Turn();
    void TurnResult(const Point& lastHit, int result);
    void EnemyTurnResult(const Point& lastHit, int result);
    void Wait();
    void BattleEnd(bool winner);
};

#endif // RANDOMBOT_H
