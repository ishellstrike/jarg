#ifndef ITEMGROUP_H
#define ITEMGROUP_H
#include "itemdata.h"
#include <QObject>

class ItemGroup : public QObject
{
    Q_OBJECT
public:
    ItemGroup();
    QVector<ItemData> list;
};

#endif // ITEMGROUP_H
