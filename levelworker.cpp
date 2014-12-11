#include "levelworker.h"
#include "jmath.h"

LevelWorker::LevelWorker(QObject *parent) :
    QObject(parent)
{
    active = new SectorList();
    mem = new SectorList();
}

LevelWorker::~LevelWorker()
{
    delete active;
    delete mem;
}

Sector *LevelWorker::getSector(int x, int y)
{
    if(active->data.contains(vec2(x,y)))
    Sector *sec = new Sector(x, y);
    sec->Rebuild();
    active->data.push_back(sec);
    return sec;
}
