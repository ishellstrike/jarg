#include "blockdata.h"

BlockData::BlockData(QObject *parent) :
    QObject(parent),
    m_name(),
    m_description(),
    m_symbol('?'),
    m_id(),
    m_color(),
    m_height(1),
    m_texture("error")
{

}

BlockData &BlockData::operator=(const BlockData &val)
{
    if (this != &val)
    {
        m_id = val.m_id;
        m_name = val.m_name;
        m_description = val.m_description;
        m_color = val.m_color;
        m_symbol = val.m_symbol;
        m_height = val.m_height;
        m_texture = val.m_texture;
    }
    return *this;
}

BlockData::BlockData(const BlockData &val) :
    m_name(val.m_name),
    m_description(val.m_description),
    m_color(val.m_color),
    m_symbol(val.m_symbol),
    m_id(val.m_id),
    m_height(val.m_height),
    m_texture(val.m_texture)
{
}
