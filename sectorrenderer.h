#ifndef SECTORRENDERER_H
#define SECTORRENDERER_H

#include "agent.h"

#include <QObject>

class SectorRenderer : public QObject
{
    Q_OBJECT
public:
    explicit SectorRenderer(QObject *parent = 0);

signals:

public slots:

public:
    QString name();
};

#endif // SECTORRENDERER_H
