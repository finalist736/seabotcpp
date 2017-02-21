#include "linerbot.h"

LinerBot::LinerBot(QObject *parent):
    TcpBot(parent), currentPoint(Point{0, 0})
{
    SetAuthKey("qwerty");
}

void LinerBot::Auth()
{
    TcpBot::Auth();
}

void LinerBot::BattleStart(int opponentID, const QString &opponentName)
{
    //qDebug() << "opponentID:" << opponentID << "opponentName:" << opponentName;
}

Point LinerBot::Turn()
{
    if (currentPoint.x == 10) {
        currentPoint.x = 0;
        currentPoint.y++;
    }
    Point result = currentPoint;
    currentPoint.x++;
    return result;
}

void LinerBot::TurnResult(const Point &lastHit, int result)
{
    if (result == 1) {
        //qDebug() << "BOOM!";
    } else {
        //qDebug() << "miss...";
    }
}

void LinerBot::EnemyTurnResult(const Point &lastHit, int result)
{
    if (result == 1) {
        //qDebug() << "OOPS";
    } else {
        //qDebug() << "haha";
    }
}

void LinerBot::Wait()
{

}

void LinerBot::BattleEnd(bool win)
{
    if (win){
        //qDebug() << "URA!";
        emit Win("Linear");
    } else {
        //qDebug() << "I'll be back!";
    }
}
