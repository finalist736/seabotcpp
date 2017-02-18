#include <QCoreApplication>
#include <QDebug>
#include <QDateTime>
#include "linerbot.h"
#include "randombot.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qsrand(QDateTime::currentDateTime().toTime_t());

    RandomBot * rbot = new RandomBot();
    rbot->connectToHost("127.0.0.1", 11000);


    LinerBot * bot = new LinerBot(&a);
    bot->connectToHost("127.0.0.1", 11000);

    return a.exec();
}
