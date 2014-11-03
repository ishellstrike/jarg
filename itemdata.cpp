#include "itemdata.h"

ItemData::ItemData() :
    ObjectData(),
    m_color(),
    flags(),
    m_weight()
{

}

ItemData &ItemData::operator=(const ItemData &val)
{
    if (this != &val)
    {
        m_color = val.m_color;
        flags = val.flags;
        m_weight = val.m_weight;
    }
    return *this;
}

ItemData::ItemData(const ItemData &val) :
    m_color(val.m_color),
    flags(val.flags),
    m_weight(val.m_weight)
{
}

ObjectData::ObjectData(const ObjectData &val) :
    m_name(val.m_name),
    m_description(val.m_description),
    m_symbol(val.m_symbol),
    m_id(val.m_id)
{
}

QString ItemData::toString() const
{
    QString a;
    a.append("ItemData : ").append(id());
    return a;
}

ObjectData &ObjectData::operator=(const ObjectData &val)
{
    if (this != &val)
    {
        m_id = val.m_id;
        m_name = val.m_name;
        m_description = val.m_description;
        m_symbol = val.m_symbol;
    }
    return *this;
}

ObjectData::ObjectData() :
    m_name(),
    m_description(),
    m_id(),
    m_symbol('?')
{

}
