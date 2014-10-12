#ifndef ITEMDATA_H
#define ITEMDATA_H
#include <QColor>
#include <QVector>
#include <QObject>

struct Flag
{
    QString name;
    int value;
};

class ItemData : public QObject
{
    Q_OBJECT
    QString m_id;

public:
    ItemData();
    ItemData &operator=(const ItemData &val);
    ItemData(const ItemData &val);

    QString id() const
    {
        return m_id;
    }
    Q_PROPERTY(QString id READ id WRITE set_id)
    QColor color;
    char symbol;

    QString name;
    QString description;
    QVector<Flag> flags;

    QString toString() const;

public slots:
    void set_id(QString arg)
    {
        m_id = arg;
    }
};

class ItemGroup
{
public:
    ItemGroup();
    QVector<ItemData> list;
};

#endif // ITEMDATA_H
