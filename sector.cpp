#include "sector.h"
#include "blockdatabase.h"

#define XYZ(x,y,z)(x*RYRZ + y*RZ + z)

Sector::Sector()
{
    m_blocks = new Block[RXYZ];
}

Sector::~Sector()
{
    delete[] m_blocks;
}

void Sector::setBlock(int x, int y, int z, const QString &id)
{
    auto temp = BlockDataBase::getBlockData(id);
    m_blocks[XYZ(x,y,z)].data = temp;
}

void Sector::setBlock(int x, int y, int z, const Block &block)
{

}

const Block *Sector::getBlock(int x, int y, int z) const
{
    return &m_blocks[XYZ(x,y,z)];
}
