#ifndef BLOCK_H
#define BLOCK_H
#include "blockdata.h"
#include "object.h"
#include "jatlas.h"

class Block : public Object
{
public:
    Block();
    ~Block();
    Q_PROPERTY(BlockData* data READ data WRITE data);
    QVector2D source();

    // Object interface
    QString id();
    QString name();
    QString description();
    float height();
    BlockData* data() const
    {
        return m_data;
    }

public slots:
    void data(BlockData* arg)
    {
        m_data = arg;
        m_source = JAtlas::instance()->sources[arg->texture()];
    }

private:
    QVector2D m_source;
    BlockData* m_data;
};

#endif // BLOCK_H
