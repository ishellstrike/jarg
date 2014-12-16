#include "levelworker.h"
#include "jmath.h"
#include "sector.h"

LevelWorker::LevelWorker(QObject *parent) :
    QObject(parent)
{
    active = new SectorList();
    mem = new SectorList();
    qDebug() << "init level worker";
}

LevelWorker::~LevelWorker()
{
    delete active;
    delete mem;
}

Sector *LevelWorker::getSector(int x, int y)
{
    Sector *sect;
    if(!active->data.contains(vec2hash(x, y)))
        sect = new Sector(x, y);
    else
        sect = active->data[vec2hash(x, y)];
    sect->Rebuild();
    active->data.insert(vec2hash(x, y), sect);
    return sect;
}
