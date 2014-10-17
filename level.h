#ifndef LEVEL_H_
#define LEVEL_H_
#include "glwidget.h"
#include "levelworker.h"
#include "sectorlist.h"

class Level : public QObject
{
    Q_OBJECT
    SectorList *toRender;
    LevelWorker *worker;
public:
    explicit Level(QObject *parent = 0);
    void render(GLWidget *parent);
    void preload(int x, int y);
signals:

public slots:

};

#endif // LEVEL_H
