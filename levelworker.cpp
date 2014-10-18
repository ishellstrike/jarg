#include "levelworker.h"

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
    Sector *sec = new Sector();
    sec->Rebuild();
    active->data.push_back(sec);
    return sec;
}
