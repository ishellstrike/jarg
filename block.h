#ifndef BLOCK_H
#define BLOCK_H
#include "blockdata.h"
#include "object.h"

class Block : public Object
{
public:
    Block();
    ~Block();
    BlockData *data;

    // Object interface
public:
    QString id();
    QString name();
    QString description();
};

#endif // BLOCK_H
