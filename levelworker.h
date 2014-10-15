#ifndef LEVELWORKER_H
#define LEVELWORKER_H

#include "sector.h"

#include <QObject>

class LevelWorker : public QObject
{
    Q_OBJECT
public:
    explicit LevelWorker(QObject *parent = 0);
    QVector<Sector *> active; //render
    QVector<Sector *> far;
    QVector<Sector *> mem;
signals:

public slots:

};

#endif // LEVELWORKER_H
