#include "itemdata.h"

ItemData::ItemData() :
    m_name(),
    m_description(),
    m_color(),
    m_symbol('?'),
    m_id(),
    flags(),
    m_weight()
{

}

ItemData &ItemData::operator=(const ItemData &val)
{
    if (this != &val)
    {
        m_id = val.m_id;
        m_name = val.m_name;
        m_description = val.m_description;
        m_color = val.m_color;
        m_symbol = val.m_symbol;
        flags = val.flags;
        m_weight = val.m_weight;
    }
    return *this;
}

ItemData::ItemData(const ItemData &val) :
    m_name(val.m_name),
    m_description(val.m_description),
    m_color(val.m_color),
    m_symbol(val.m_symbol),
    m_id(val.m_id),
    flags(val.flags),
    m_weight(val.m_weight)
{
}

QString ItemData::toString() const
{
    QString a;
    a.append("ItemData : ").append(id());
    return a;
}
