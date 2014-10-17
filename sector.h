#ifndef SECTOR_H_
#define SECTOR_H_

#include "block.h"
#include <QObject>
#include <QVector>
#include "glwidget.h"
#include <QtWidgets>
#include <QGLWidget>
#include "vertex.h"
#include <QOpenGLVertexArrayObject>

#define RX 25
#define RY 25
#define RZ 10
#define RYRZ RY*RZ
#define RXYZ RX*RY*RZ

class Sector : public QObject
{
    Q_OBJECT
    Block *m_blocks;
    QVector<Vertex> geom;
    QVector<GLuint> indeces;
    QVector2D offset;
    QOpenGLVertexArrayObject *m_vao;
public:
    Sector();
    virtual ~Sector();
    void render(GLWidget *parent);

    void Rebuild(GLWidget *parent);
signals:

public slots:
    void setBlock(int x, int y, const QString &id);
    void setBlock(int x, int y, const Block &block);
    const Block *getBlock(int x, int y) const;
};

#endif // SECTOR_H
