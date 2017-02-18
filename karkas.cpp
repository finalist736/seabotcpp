#include "karkas.h"

Karkas::Karkas(QObject *parent):
    TcpBot(parent)
{

}

void Karkas::Auth()
{

}

Point Karkas::Turn()
{
    return Point{0,0};
}

void Karkas::TurnResult(const Point &lastHit, int result)
{

}

void Karkas::EnemyTurnResult(const Point &lastHit, int result)
{

}

void Karkas::Wait()
{

}

void Karkas::BattleEnd(bool)
{

}
