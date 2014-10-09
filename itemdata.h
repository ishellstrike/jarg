#ifndef ITEMDATA_H
#define ITEMDATA_H
#include <QColor>
#include <QVector>

struct Flag
{
    QString name;
    int value;
};

class ItemData
{
public:
    ItemData();

    QString id;
    QColor color;
    char symbol;

    QString name;
    QString description;
    QVector<Flag> flags;
};

class ItemGroup
{
public:
    ItemGroup();
    QVector<ItemData> list;
};

#endif // ITEMDATA_H
