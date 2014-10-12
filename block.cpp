#include "block.h"
#include "object.h"

Block::Block()
{

}

QString Block::id()
{
    return data.id();
}

QString Block::name()
{
    return data.name;
}

QString Block::description()
{
    return data.description;
}
