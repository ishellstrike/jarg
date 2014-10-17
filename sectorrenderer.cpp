#include "sectorrenderer.h"

SectorRenderer::SectorRenderer(QObject *parent) :
    QObject(parent)
{
}

QString SectorRenderer::name()
{
    return "SectorRenderer";
}
