#include "level.h"

Level::Level(QObject *parent) :
    QObject(parent)
{
}

void Level::render(GLWidget *parent)
{
    for(Sector *a : toRender->data)
    {
        a->render(parent);
    }
}

void Level::preload(int x, int y)
{
    worker->getSector(x, y);
}
