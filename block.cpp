#include "block.h"
#include "object.h"

Block::Block() :
    m_data(nullptr)
{

}

Block::~Block()
{
    m_data = nullptr;
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
