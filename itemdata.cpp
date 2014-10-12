#include "itemdata.h"

ItemData::ItemData()
{
}

ItemData &ItemData::operator=(const ItemData &val)
{
    return ItemData(val);
}

ItemData::ItemData(const ItemData &val)
{
    set_id(val.id());
}

QString ItemData::toString() const
{
    QString a;
    a.append("ItemData : ").append(id());
    return a;
}
