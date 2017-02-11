#include "randombot.h"
#include <QDebug>


RandomBot::RandomBot()
{
    mAuthKey = "1231231231231312213";
    for (int i=0;i<10;i++)
    {
        for (int j=0;j<10;j++)
        {
            arr.append(Point{i,j});
        }
    }
}

Point RandomBot::Turn()
{
    int rnd1 = qrand() % arr.length();
    Point a = arr[rnd1];
    arr.removeAt(rnd1);

    //qDebug() << "turn";
    return a;
}

void RandomBot::TurnResult(const Point &lastHit, int result)
{
    qDebug() << "RandomBot::TurnResult" << lastHit.y << lastHit.x << result;
}

void RandomBot::EnemyTurnResult(const Point &lastHit, int result)
{
    qDebug() << "RandomBot::EnemyTurnResult" << lastHit.y << lastHit.x << result;
}

void RandomBot::Wait()
{
    qDebug() << "waiting for bvb opponent";
}

void RandomBot::BattleEnd(bool winner)
{
    qDebug() << (winner ? "winner" : "loser");
}

