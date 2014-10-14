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
//    Block *block = m_blocks[XY(i,j)];
//    var h = block->height();
//    //var l = (short)(c.Count/6*4);
//    if (j == RY - 1 || !m_blocks[XY(i,j+1)].isWallmaker() || m_blocks[(XY(i,j+1)].isWallmaker() < 32)
//    {
//        b.Add(Vertex(QVector3D(i, j + 1, h), BACK,
//                     block.source()));
//        b.Add(Vertex(QVector3D(i + 1, j + 1, h), BACK,
//                     block.Source + QVector2D(Atlases.Instance.SpriteWidth, 0)));
//        b.Add(Vertex(QVector3D(i, j + 1, 0), BACK,
//                     block.Source + QVector2D(0, Atlases.Instance.SpriteHeight)));
//        b.Add(Vertex(QVector3D(i + 1, j + 1, 0), BACK,
//                     block.Source + QVector2D(Atlases.Instance.SpriteWidth, Atlases.Instance.SpriteHeight)));
//        c.Add((short) (l + 0));
//        c.Add((short) (l + 1));
//        c.Add((short) (l + 2));
//        c.Add((short) (l + 3));
//        c.Add((short) (l + 2));
//        c.Add((short) (l + 1));
//        l += 4;
//    }
//    if (j == 0 || !m_blocks[XY(i,j-1)].isWallmaker() || m_blocks[XY(i,j-1)].isWallmaker() < 32)
//    {
//        b.Add(Vertex(QVector3D(i, j, h), RIGHT,
//                     block.Source));
//        b.Add(Vertex(QVector3D(i, j, 0), RIGHT,
//                     block.Source + QVector2D(0, Atlases.Instance.SpriteHeight)));
//        b.Add(Vertex(QVector3D(i + 1, j, h), RIGHT,
//                     block.Source + QVector2D(Atlases.Instance.SpriteWidth, 0)));
//        b.Add(Vertex(QVector3D(i + 1, j, 0), RIGHT,
//                     block.Source + QVector2D(Atlases.Instance.SpriteWidth, Atlases.Instance.SpriteHeight)));
//        c.Add((short) (l + 0));
//        c.Add((short) (l + 1));
//        c.Add((short) (l + 2));
//        c.Add((short) (l + 2));
//        c.Add((short) (l + 1));
//        c.Add((short) (l + 3));
//        l += 4;
//    }
//    if (i == 0 || !m_blocks[XY(i-1,j)].isWallmaker() || m_blocks[XY(i-1,j)].isWallmaker() < 32)
//    {
//        b.Add(Vertex(QVector3D(i, j, h), FORWARD,
//                     block.Source));
//        b.Add(Vertex(QVector3D(i, j + 1, h), FORWARD,
//                     block.Source + new QVector2D(Atlases.Instance.SpriteWidth, 0)));
//        b.Add(Vertex(QVector3D(i, j, 0), FORWARD,
//                     block.Source + new QVector2D(0, Atlases.Instance.SpriteHeight)));
//        b.Add(Vertex(QVector3D(i, j + 1, 0), FORWARD,
//                     block.Source + QVector2D(Atlases.Instance.SpriteWidth, Atlases.Instance.SpriteHeight)));
//        c.Add((short)(l + 0));
//        c.Add((short)(l + 1));
//        c.Add((short)(l + 2));
//        c.Add((short)(l + 1));
//        c.Add((short)(l + 3));
//        c.Add((short)(l + 2));
//        l += 4;
//    }
//    if (i == RX - 1 || !m_blocks[XY(i+1,j)].Data.Wallmaker || m_blocks[XY(i+1,j)].Data.Height < 32)
//    {
//        b.Add(Vertex(QVector3D(i + 1, j, h), LEFT,
//                     block.Source));
//        b.Add(Vertex(QVector3D(i + 1, j, 0), LEFT,
//                     block.Source + new Vector2(0, Atlases.Instance.SpriteHeight)));
//        b.Add(Vertex(QVector3D(i + 1, j + 1, h), LEFT,
//                     block.Source + new Vector2(Atlases.Instance.SpriteWidth, 0)));
//        b.Add(Vertex(QVector3D(i + 1, j + 1, 0), LEFT,
//                     block.Source + QVector2D(Atlases.Instance.SpriteWidth, Atlases.Instance.SpriteHeight)));
//        c.Add((short)(l + 0));
//        c.Add((short)(l + 1));
//        c.Add((short)(l + 2));
//        c.Add((short)(l + 2));
//        c.Add((short)(l + 1));
//        c.Add((short)(l + 3));
//        l += 4;
//    }
//    b.Add(Vertex(QVector3D(i, j, h), UP,
//                 block.Source));
//    b.Add(Vertex(QVector3D(i + 1, j, h), UP,
//                 block.Source + new Vector2(Atlases.Instance.SpriteWidth, 0)));
//    b.Add(Vertex(QVector3D(i, j + 1, h), UP,
//                 lock.Source + new Vector2(0, Atlases.Instance.SpriteHeight)));
//    b.Add(Vertex(QVector3D(i + 1, j + 1, h), UP,
//                 block.Source + QVector2D(Atlases.Instance.SpriteWidth, Atlases.Instance.SpriteHeight)));
//    c.Add((short) (l + 0));
//    c.Add((short) (l + 1));
//    c.Add((short) (l + 2));
//    c.Add((short) (l + 1));
//    c.Add((short) (l + 3));
//    c.Add((short) (l + 2));
//    l += 4;
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
