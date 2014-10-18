#ifndef BLOCKDATA_H
#define BLOCKDATA_H
#include <string>
#include <QtOpenGL>
#include <QObject>

class BlockData : public QObject
{
    Q_OBJECT
    QString m_id;
    QColor m_color;
    QString m_name;
    QString m_description;
    QString m_texture;
    float m_height;
    char m_symbol;

public:
    explicit BlockData(QObject *parent = nullptr);
    BlockData &operator=(const BlockData &val);
    BlockData(const BlockData &val);

    QString id() const
    {
        return m_id;
    }
    Q_PROPERTY(QString id READ id WRITE id)
    Q_PROPERTY(QColor color READ color WRITE color)
    Q_PROPERTY(QString name READ name WRITE name)
    Q_PROPERTY(QString description READ description WRITE description)
    Q_PROPERTY(QString texture READ texture WRITE texture)
    Q_PROPERTY(float height READ height WRITE height)
    Q_PROPERTY(char symbol READ symbol WRITE symbol)

    QColor color() const
    {
        return m_color;
    }
    QString name() const
    {
        return m_name;
    }
    QString description() const
    {
        return m_description;
    }
    QString texture() const
    {
        return "grass";
    }
    float height() const
    {
        return m_height;
    }
    char symbol() const
    {
        return m_symbol;
    }

public slots:
    void id(QString arg)
    {
        m_id = arg;
    }
    void color(QColor arg)
    {
        m_color = arg;
    }
    void name(QString arg)
    {
        m_name = arg;
    }
    void description(QString arg)
    {
        m_description = arg;
    }
    void texture(QString arg)
    {
        m_texture = arg;
    }
    void height(float arg)
    {
        m_height = arg;
    }
    void symbol(char arg)
    {
        m_symbol = arg;
    }
};

#endif // BLOCKDATA_H
