#ifndef SPRITEBATCH_H
#define SPRITEBATCH_H
#include "jtexture.h"
#include "graphics.h"

#include <QGLShaderProgram>
#include <QVector3D>
#include <QOpenGLBuffer>

#define SIZE 10000

class SpriteBatch
{
public:
    SpriteBatch(JGraphics *parent, QOpenGLContext *context);
    ~SpriteBatch();

    QVector3D *pos;
    QVector2D *uv;
    QColor *col;
    unsigned int *index;
    unsigned int cur;

    QOpenGLBuffer vert_b, col_b, uv_b, ind_b;
    QOpenGLVertexArrayObject vao;

    JGraphics *m_parent;
    QOpenGLContext *m_context;
    int current;

    QGLShaderProgram *program;

    void DrawQuad(QVector2D loc, QVector2D size, const JTexture &tex);
    void DrawRect(QVector2D loc, QVector2D size, QColor col);
    void Render();
};

#endif // SPRITEBATCH_H
