#ifndef WINSCOUNTER_H
#define WINSCOUNTER_H

#include <QObject>
#include <QMutex>
#include <QMap>

class WinsCounter : public QObject
{
    Q_OBJECT
private:
    int counts;
    QMutex mu;
    QMap<QString, int> mWinsCount;
public:
    explicit WinsCounter(QObject *parent = 0);

signals:

public slots:
    void Win(QString name);
};

#endif // WINSCOUNTER_H
