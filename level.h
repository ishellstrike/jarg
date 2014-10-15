#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include <QVector>
#include "sector.h"

class Level : public QObject
{
    Q_OBJECT
public:
    explicit Level(QObject *parent = 0);
    QVector<Sector *> active;
signals:

public slots:

};

#endif // LEVEL_H
