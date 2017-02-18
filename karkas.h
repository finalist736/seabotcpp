#ifndef KARKAS_H
#define KARKAS_H

#include "tcpbot.h"

class Karkas : public TcpBot
{
public:
    Karkas(QObject *parent = 0);

    void Auth();

    void BattleStart(int opponentID, const QString& opponentName);
    Point Turn();
    void TurnResult(const Point& lastHit, int result);
    void EnemyTurnResult(const Point& lastHit, int result);
    void Wait();
    void BattleEnd(bool);
};

#endif // KARKAS_H
