#include "spritebatch.h"
#include <QGLFunctions>
#include "jatlas.h"


SpriteBatch::SpriteBatch(JGraphics *parent, QOpenGLContext *context) :
    m_parent(parent),
    m_context(context),
    current(-1),
    cur(0)
{
    index = new unsigned int[SIZE*6];
    uv = new QVector2D[SIZE*4];
    pos = new QVector3D[SIZE*4];
    col = new QColor[SIZE*4];
    vert_b.create();
    col_b.create();
    uv_b.create();
    ind_b.create();
    vao.create();

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1
#define PROGRAM_COLOR_ATTRIBUTE 2

    program = new QOpenGLShaderProgram();
    loadShader("data/shaders/simple.vert", "data/shaders/simple.frag", program);

    program->bind();
    program->setUniformValue("colorTexture", 0);
}

SpriteBatch::~SpriteBatch()
{
    delete[] index;
    delete[] uv;
    delete[] pos;
    delete[] col;

    vert_b.destroy();
    col_b.destroy();
    uv_b.destroy();
    ind_b.destroy();
    vao.destroy();
}

void SpriteBatch::DrawQuadAtlas(vec2 loc, vec2 size, QString num)
{
    auto inst = JAtlas::instance();
    if(inst->tex->textureId != current)
    {
        Render();
        current = inst->tex->textureId;
    }
    if(cur >= SIZE - 1)
        Render();

    auto f = inst->sources.find(num);
    if(f == inst->sources.end())
        return;

    pos[cur*4]     = vec3(loc.x(), loc.y(), 0);
    pos[cur*4 + 1] = vec3(loc.x() + size.x(), loc.y(), 0);
    pos[cur*4 + 2] = vec3(loc.x() + size.x(), loc.y() + size.y(), 0);
    pos[cur*4 + 3] = vec3(loc.x(), loc.y() + size.y(), 0);

    col[cur*4]     = Qt::white;
    col[cur*4 + 1] = Qt::white;
    col[cur*4 + 2] = Qt::white;
    col[cur*4 + 3] = Qt::white;

    vec2 source = inst->sources[num];

    uv[cur*4]      = source;
    uv[cur*4 + 1]  = source + vec2(inst->sSize.x(), 0);
    uv[cur*4 + 2]  = source + inst->sSize;
    uv[cur*4 + 3]  = source + vec2(0, inst->sSize.y());

    index[cur*6]     = cur*4;
    index[cur*6 + 1] = cur*4 + 1;
    index[cur*6 + 2] = cur*4 + 3;
    index[cur*6 + 3] = cur*4 + 1;
    index[cur*6 + 4] = cur*4 + 2;
    index[cur*6 + 5] = cur*4 + 3;

    cur++;
}

void SpriteBatch::DrawQuad(vec2 loc, vec2 size, const Texture &tex)
{
    if(tex.textureId != current)
    {
        Render();
        current = tex.textureId;
    }
    if(cur >= SIZE - 1)
        Render();

    pos[cur*4]     = vec3(loc.x(), loc.y(), 0);
    pos[cur*4 + 1] = vec3(loc.x() + size.x(), loc.y(), 0);
    pos[cur*4 + 2] = vec3(loc.x() + size.x(), loc.y() + size.y(), 0);
    pos[cur*4 + 3] = vec3(loc.x(), loc.y() + size.y(), 0);

    col[cur*4]     = Qt::white;
    col[cur*4 + 1] = Qt::white;
    col[cur*4 + 2] = Qt::white;
    col[cur*4 + 3] = Qt::white;

    uv[cur*4]      =vec2(0,0);
    uv[cur*4 + 1]  =vec2(1,0);
    uv[cur*4 + 2]  =vec2(1,1);
    uv[cur*4 + 3]  =vec2(0,1);

    index[cur*6]     = cur*4;
    index[cur*6 + 1] = cur*4 + 1;
    index[cur*6 + 2] = cur*4 + 3;
    index[cur*6 + 3] = cur*4 + 1;
    index[cur*6 + 4] = cur*4 + 2;
    index[cur*6 + 5] = cur*4 + 3;

    cur++;
}

void SpriteBatch::DrawRect(vec2 loc, vec2 size, QColor _col)
{
    if(cur >= SIZE - 1)
        Render();

    pos[cur*4]     = vec3(loc.x(), loc.y(), 0);
    pos[cur*4 + 1] = vec3(loc.x() + size.x(), loc.y(), 0);
    pos[cur*4 + 2] = vec3(loc.x() + size.x(), loc.y() + size.y(), 0);
    pos[cur*4 + 3] = vec3(loc.x(), loc.y() + size.y(), 0);

    col[cur*4]     = _col;
    col[cur*4 + 1] = _col;
    col[cur*4 + 2] = _col;
    col[cur*4 + 3] = _col;

    uv[cur*4]      = vec2(0,0);
    uv[cur*4 + 1]  = vec2(1,0);
    uv[cur*4 + 2]  = vec2(1,1);
    uv[cur*4 + 3]  = vec2(0,1);

    index[cur*6]     = cur*4;
    index[cur*6 + 1] = cur*4 + 1;
    index[cur*6 + 2] = cur*4 + 3;
    index[cur*6 + 3] = cur*4 + 1;
    index[cur*6 + 4] = cur*4 + 2;
    index[cur*6 + 5] = cur*4 + 3;

    cur++;
}

void SpriteBatch::Render()
{
    glEnable(GL_BLEND);
    if(cur == 0)
        return;

    m_parent->glBindBuffer(GL_ARRAY_BUFFER, vert_b.bufferId());
    m_parent->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*cur*4, &pos[0], GL_STREAM_DRAW);
    m_parent->glEnableVertexAttribArray(PROGRAM_VERTEX_ATTRIBUTE);
    m_parent->glVertexAttribPointer(PROGRAM_VERTEX_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), 0);

    m_parent->glBindBuffer(GL_ARRAY_BUFFER, col_b.bufferId());
    m_parent->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D)*cur*4, &uv[0], GL_STREAM_DRAW);
    m_parent->glEnableVertexAttribArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    m_parent->glVertexAttribPointer(PROGRAM_TEXCOORD_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, sizeof(QVector2D), 0);

    m_parent->glBindBuffer(GL_ARRAY_BUFFER, uv_b.bufferId());
    m_parent->glBufferData(GL_ARRAY_BUFFER, sizeof(QColor)*cur*4, &col[0], GL_STREAM_DRAW);
    m_parent->glEnableVertexAttribArray(PROGRAM_COLOR_ATTRIBUTE);
    m_parent->glVertexAttribPointer(PROGRAM_COLOR_ATTRIBUTE, 4, GL_FLOAT, GL_FALSE, sizeof(QColor), 0);

    m_parent->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ind_b.bufferId());
    m_parent->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*cur*6, &index[0], GL_STREAM_DRAW);

    m_parent->glDrawElements(GL_TRIANGLES, cur*6, GL_UNSIGNED_INT, NULL);

    cur = 0;
}
