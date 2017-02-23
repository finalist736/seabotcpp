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

void RandomBot::BattleStart(int opponentID, const QString &opponentName)
{
    qDebug() << "My ID:" << MyID();
    qDebug() << "opponentID:" << opponentID << "opponentName:" << opponentName;
}

Point RandomBot::Turn()
{
    if (arr.length() == 0) {
        return Point{0,0};
    }
    int rnd1 = qrand() % arr.length();
    Point a = arr[rnd1];
    arr.removeAt(rnd1);
    return a;
}

void RandomBot::TurnResult(const Point &lastHit, int result)
{
    qDebug() << "* [" << lastHit.y << ", " << lastHit.x << "] = " << result;
}

void RandomBot::EnemyTurnResult(const Point &lastHit, int result)
{
    qDebug() << "  [" << lastHit.y << ", " << lastHit.x << "] = " << result;
}

void RandomBot::Wait()
{
    qDebug() << "waiting for bvb opponent";
}

void RandomBot::BattleEnd(bool winner)
{
    if (winner){
        qDebug() << "URA!";
        emit Win(QString("Random"));
    } else {
        qDebug() << "I'll be back!";
    }
}

