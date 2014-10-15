#include "levelworker.h"

LevelWorker::LevelWorker(QObject *parent) :
    QObject(parent),
    active(),
    mem()
{
}

LevelWorker::~LevelWorker()
{
    delete active;
    active = nullptr;
    delete mem;
    mem = nullptr;
}
