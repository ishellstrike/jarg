#include "block.h"
#include "object.h"

Block::Block() :
    m_data(nullptr),
    m_source()
{

}

Block::~Block()
{
    m_data = nullptr;
}

QVector2D Block::source()
{
    return m_source;
}

QString Block::id()
{
    if(m_data) return "";
    return m_data->id();
}

QString Block::name()
{
    if(m_data) return "";
    return m_data->name();
}

QString Block::description()
{
    if(m_data) return "";
    return m_data->description();
}

float Block::height()
{
    if(m_data) return 1;
    return m_data->height();
}
