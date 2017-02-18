#ifndef LINERBOT_H
#define LINERBOT_H

#include "tcpbot.h"

class LinerBot : public TcpBot
{
private:
    Point currentPoint;
public:
    LinerBot(QObject *parent = 0);

    void Auth();
    Point Turn();
    void TurnResult(const Point& lastHit, int result);
    void EnemyTurnResult(const Point& lastHit, int result);
    void Wait();
    void BattleEnd(bool);
};

#endif // LINERBOT_H
