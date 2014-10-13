#ifndef SECTOR_H
#define SECTOR_H
#include "block.h"
#include <QObject>
#define RX 25
#define RY 25
#define RZ 10
#define RYRZ RY*RZ
#define RXYZ RX*RY*RZ

class Sector : public QObject
{
    Q_OBJECT
    Block *m_blocks;
public:
    Sector();
    virtual ~Sector();

signals:

public slots:
    void setBlock(int x, int y, int z, const QString &id);
    void setBlock(int x, int y, int z, const Block &block);
    const Block *getBlock(int x, int y, int z) const;
};

#endif // SECTOR_H
