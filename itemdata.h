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

struct RPart
{
    QString name;
    int quality;
    int count;
};

class ObjectData : public QObject
{
    Q_OBJECT
    QString m_id;
    QString m_name;
    QString m_description;
    char m_symbol;
public:
    ObjectData();

    Q_PROPERTY(char symbol READ symbol WRITE symbol)
    Q_PROPERTY(QString id READ id WRITE id)
    Q_PROPERTY(QString name READ name WRITE name)
    Q_PROPERTY(QString description READ description WRITE description)

    QString name() const
    {
        return m_name;
    }
    QString id() const
    {
        return m_id;
    }
    QString description() const
    {
        return m_description;
    }
    char symbol() const
    {
        return m_symbol;
    }
    ObjectData &operator =(const ObjectData &val);
    ObjectData(const ObjectData &val);
public slots:
    void id(QString arg)
    {
        m_id = arg;
    }
    void name(QString arg)
    {
        m_name = arg;
    }
    void description(QString arg)
    {
        m_description = arg;
    }
    void symbol(char arg)
    {
        m_symbol = arg;
    }
};

class ItemData : public ObjectData
{
    Q_OBJECT
    QColor m_color;

    int m_weight;

public:
    ItemData();
    ItemData &operator=(const ItemData &val);
    ItemData(const ItemData &val);

    Q_PROPERTY(QColor color READ color WRITE color)
    Q_PROPERTY(int weight READ weight WRITE weight)


    QVector<Flag> flags;

    QString toString() const;

    QColor color() const
    {
        return m_color;
    }

    int weight() const
    {
        return m_weight;
    }

public slots:
    void color(QColor arg)
    {
        m_color = arg;
    }
    void weight(int arg)
    {
        m_weight = arg;
    }
};

#endif // ITEMDATA_H
