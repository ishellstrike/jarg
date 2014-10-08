#ifndef BLOCKDATA_H
#define BLOCKDATA_H
#include <string>
#include <QtOpenGL>

class BlockData
{
public:
    BlockData();

    QString id;
    QColor color;
    char symbol;

    QString name;
    QString description;
};

#endif // BLOCKDATA_H
