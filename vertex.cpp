#include "vertex.h"

Vertex::Vertex() :
    pos(),
    normal(),
    tex()
{
}

Vertex::Vertex(QVector3D p, QVector3D n, QVector2D t) :
    pos(p),
    normal(n),
    tex(t)
{

}
