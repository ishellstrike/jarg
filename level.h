#ifndef LEVEL_H
#define LEVEL_H

#include <QObject>
#include <QVector>
#include "sector.h"
#include "sectorlist.h"

class LevelRenderer : public QObject
{
    Q_OBJECT
    SectorList *toRender;
public:
    explicit LevelRenderer(QObject *parent = 0);
    void Render();
signals:

public slots:

};

#endif // LEVEL_H
