#ifndef BLOCKDATA_H
#define BLOCKDATA_H
#include <string>
#include <QtOpenGL>
#include <QObject>

class BlockData : public QObject
{
    Q_OBJECT
    QString m_id;

public:
    BlockData();
    BlockData &operator=(const BlockData &val);
    BlockData(const BlockData &val);

    QString id() const
    {
        return m_id;
    }
    Q_PROPERTY(QString id READ id WRITE set_id)
    QColor color;
    char symbol;

    QString name;
    QString description;

public slots:
    void set_id(QString arg)
    {
        m_id = arg;
    }
};

#endif // BLOCKDATA_H
