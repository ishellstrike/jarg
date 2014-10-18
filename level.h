#ifndef LEVEL_H_
#define LEVEL_H_
#include "levelworker.h"
#include "sectorlist.h"

class Level : public QObject
{
    Q_OBJECT
    SectorList *toRender; //owned by worker
    LevelWorker *worker; //owned by game instance
public:
    explicit Level(QObject *parent = 0);
    void render();
    void preload(int x, int y);
    void setWorker(LevelWorker *w);
signals:

public slots:

};

#endif // LEVEL_H
