#ifndef SECTOR_H_
#define SECTOR_H_

#include "block.h"
#include <QObject>
#include <QVector>
#include "agent.h"
#include "graphics.h"
#include "vertex.h"

#define RX 25
#define RY 25
#define RXY RX*RY

class Sector : public QObject
{
    Q_OBJECT
    Block *m_blocks;
    QVector<Vertex> geom;
    QVector<GLuint> indeces;
public:
    Sector(int x_, int y_);
    virtual ~Sector();
    void render(abstract_engine *eng);
    vec2 offset;
    void Rebuild();
signals:

public slots:
    void setBlock(int x, int y, const QString &id);
    void setBlock(int x, int y, const Block &block);
    const Block *getBlock(int x, int y) const;
};

#endif // SECTOR_H
