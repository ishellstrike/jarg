#ifndef SECTORLIST_H
#define SECTORLIST_H

#include "sector.h"
#include <QVector>
#include <QObject>

struct SectorList
{
    QVector<Sector *> data;
    SectorList();
    ~SectorList();
};

#endif // SECTORLIST_H
