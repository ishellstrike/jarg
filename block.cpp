#include "block.h"
#include "object.h"

Block::Block()
{

}

Block::~Block()
{
    data = nullptr;

}

QString Block::id()
{
    if(data) return "";
    return data->id();
}

QString Block::name()
{
    if(data) return "";
    return data->name;
}

QString Block::description()
{
    if(data) return "";
    return data->description;
}
