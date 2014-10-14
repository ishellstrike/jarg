#ifndef VERTEX_H
#define VERTEX_H
#include <QtOpenGL>

class Vertex
{
public:
    Vertex();
    Vertex(QVector3D p, QVector3D n, QVector2D t);
    QVector2D tex;
    QVector3D pos;
    QVector3D normal;
};

#endif // VERTEX_H
