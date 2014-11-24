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
    QMatrix4x4 uni;

    JGraphics *m_parent;
    QOpenGLContext *m_context;
    int current;

    QOpenGLShaderProgram *texture_program, *color_program, *current_program;

    void bind(QOpenGLShaderProgram *prog);

    void drawQuad(vec2 loc, vec2 size, const Texture &tex);
    void drawQuadAtlas(vec2 loc, vec2 size, QString num);
    void drawRect(vec2 loc, vec2 size, col4 col);
    void render();
    void setUniform(QMatrix4x4 mat);
};

#endif // SPRITEBATCH_H
