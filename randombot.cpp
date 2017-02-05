#include "randombot.h"
#include <QDebug>


RandomBot::RandomBot()
{
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
    //qDebug() << "turn result" << lastHit << result;
}
