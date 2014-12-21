#include "level.h"
#include "settings.h"

Level::Level(QObject *parent) :
    QObject(parent),
    worker(nullptr)
{
    toRender = new SectorList;
    qDebug() << "level init";
}

void Level::render(QPainter *eng)
{
    for(Sector *a : toRender->data)
    {
        if((a->offset.x()*32*32 <= Settings::instance()->resolution.width() && a->offset.x()*32*32 >= 0) ||
           (a->offset.y()*32*32 <= Settings::instance()->resolution.height() && a->offset.y()*32*32 >= 0))
        a->render(eng);
    }
}

void Level::preload(int x, int y)
{
    if(toRender->data.contains(vec2hash(x, y)))
       return;
    Sector *sec = worker->getSector(x, y);
    if(sec)
    {
        toRender->data.insert(vec2hash(x, y), sec);
    }
}

void Level::preloadRange(int x, int y, int r)
{
    for(int i = x - r; i<= x + r; i++)
        for(int j = y - r; j<= y + r; j++)
        {
                preload(i, j);
        }
}



void Level::setWorker(LevelWorker *w)
{
    worker = w;
    qDebug() << "link level worker";
}
