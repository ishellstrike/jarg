#ifndef BLOCKDATA_H
#define BLOCKDATA_H
#include <string>
#include <QtOpenGL>
#include <QObject>

class BlockData
{
public:
    BlockData();

    QString id;
    QColor color;
    char symbol;

    QString name;
    QString description;
signals:
public slots:
};

#endif // BLOCKDATA_H
