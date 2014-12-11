#ifndef SECTORLIST_H
#define SECTORLIST_H

#include "sector.h"
#include <QVector>
#include <QObject>
#include "jmath.h"

struct SectorList
{
    QHash<vec2, Sector *> data;
    SectorList();
    ~SectorList();

    int count();
};

#endif // SECTORLIST_H
