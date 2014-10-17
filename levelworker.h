#ifndef LEVELWORKER_H
#define LEVELWORKER_H

#include "sector.h"
#include "sectorlist.h"
#include <QObject>

class LevelWorker : public QObject
{
    Q_OBJECT
public:
    explicit LevelWorker(QObject *parent = 0);
    ~LevelWorker();
    SectorList *active;
    SectorList *mem;

    Sector *getSector();

signals:

public slots:

};

#endif // LEVELWORKER_H
