#include "sector.h"
#include "blockdatabase.h"
#include "vertex.h"
#include <QtOpenGL>
#include <QVector3D>
#include "jatlas.h"

#define XY(x,y)(x*RY + y)
#define BACK QVector3D(0, 0, -1)
#define DOWN QVector3D(0, -1, 0)
#define FORWARD QVector3D(0, 0, 1)
#define LEFT QVector3D(-1, 0, 0)
#define ONE QVector3D(1, 1, 1)
#define RIGHT QVector3D(1, 0, 0)
#define UP QVector3D(0, 1, 0)
#define ZERO QVector3D(0, 0, 0)

void AddBlockGeom(int i, int j)
{

}

void Sector::Rebuild()
{
    auto comp_off = offset*QVector3D(RX, 0, RY);
    for(int i =0;i<RX;i++)
        for(int j=0;j<RY;j++)
        {
            auto block_data = m_blocks[XY(i,j)].data();
            auto m_source = JAtlas::instance()->sources[block_data->texture()];

            int last = geom.size();

            geom.push_back(Vertex(comp_off + QVector3D(i, 0, j), UP, QVector2D()));
            geom.push_back(Vertex(comp_off + QVector3D(i + 1, 0, j), UP, QVector2D()));
            geom.push_back(Vertex(comp_off + QVector3D(i, 0, j + 1), UP, QVector2D()));
            geom.push_back(Vertex(comp_off + QVector3D(i + 1, 0, j + 1), UP, QVector2D()));

            indeces.push_back(last);
            indeces.push_back(last + 1);
            indeces.push_back(last + 2);
            indeces.push_back(last + 1);
            indeces.push_back(last + 3);
            indeces.push_back(last + 2);
        }
}

Sector::Sector()
{
    m_blocks = new Block[RXYZ];
}

Sector::~Sector()
{
    delete[] m_blocks;
}

void Sector::Render(QGLWidget *parent)
{

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
