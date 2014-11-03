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

    vec3 *pos;
    vec2 *uv;
    QColor *col;
    unsigned int *index;
    unsigned int cur;

    QOpenGLBuffer vert_b, col_b, uv_b, ind_b;
    QOpenGLVertexArrayObject vao;

    JGraphics *m_parent;
    QOpenGLContext *m_context;
    int current;

    QOpenGLShaderProgram *program;

    void DrawQuad(vec2 loc, vec2 size, const Texture &tex);
    void DrawQuadAtlas(vec2 loc, vec2 size, QString num);
    void DrawRect(vec2 loc, vec2 size, QColor col);
    void Render();
};

#endif // SPRITEBATCH_H
