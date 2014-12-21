#include "blockdatabase.h"
#include "sector.h"

#define XY(x,y)(x*RY + y)
#define BACK QVector3D(0, 0, -1)
#define DOWN QVector3D(0, -1, 0)
#define FORWARD QVector3D(0, 0, 1)
#define LEFT QVector3D(-1, 0, 0)
#define ONE QVector3D(1, 1, 1)
#define RIGHT QVector3D(1, 0, 0)
#define UP QVector3D(0, 1, 0)
#define ZERO QVector3D(0, 0, 0)

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1

void AddBlockGeom(int i, int j)
{

}

Sector::Sector(int x_, int y_) :
    offset(x_,y_)
{
    m_blocks = new Block[RXY];
}

Sector::~Sector()
{
    delete[] m_blocks;
    m_blocks = nullptr;
}

void Sector::render(QPainter *eng)
{
    for(int i = 0; i < RX; i++)
        for(int j = 0; j < RY; j++)
        {
           //eng->drawQuadAtlas(vec2(i*32 + offset.x()*32*32, j*32 + offset.y()*32*32), vec2(32,32), "error");
        }
}

void Sector::setBlock(int x, int y, const QString &id)
{
    auto temp = BlockDataBase::getBlockData(id);
    m_blocks[XY(x,y)].data(temp);
}

void Sector::setBlock(int x, int y, const Block &block)
{

}

const Block *Sector::getBlock(int x, int y) const
{
    return &m_blocks[XY(x,y)];
}
