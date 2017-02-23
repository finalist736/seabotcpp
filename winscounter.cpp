#include "winscounter.h"
#include <QDebug>

WinsCounter::WinsCounter(QObject *parent) :
    QObject(parent),
    counts(0)
{
    qDebug() << "WC";
}

void WinsCounter::Win(QString name)
{
    //qDebug() << name;
    mu.lock();
    if (mWinsCount.contains(name))
    {
        mWinsCount[name]++;
    }
    else
    {
        mWinsCount[name] = 1;
    }
    counts++;
    //if (counts % 10 == 0)
    //{
        qDebug() << "--------";
        qDebug() << "Random" << mWinsCount["Random"];
        qDebug() << "Linear" << mWinsCount["Linear"];
        qDebug() << "--------";
    //} else {
        //qDebug() << counts;
    //}
    mu.unlock();
}
