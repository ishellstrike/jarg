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
    uv = new vec2[SIZE*4];
    pos = new vec3[SIZE*4];
    col = new col4[SIZE*4];
    vert_b.create();
    col_b.create();
    uv_b.create();
    ind_b.create();
    vao.create();

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1
#define PROGRAM_COLOR_ATTRIBUTE 2

    texture_program = new QOpenGLShaderProgram();
    loadShader("data/shaders/simple.vert", "data/shaders/simple.frag", texture_program);

    bind(texture_program);
    texture_program->setUniformValue("colorTexture", 0);

    color_program = new QOpenGLShaderProgram();
    loadShader("data/shaders/color.vert", "data/shaders/color.frag", color_program);
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

    delete texture_program;
    delete color_program;
}

void SpriteBatch::bind(QOpenGLShaderProgram *prog)
{
    current_program = prog;
    prog->bind();
    prog->setUniformValue("MVP", uni);
}

void SpriteBatch::drawQuadAtlas(vec2 loc, vec2 size, QString num)
{
    auto inst = JAtlas::instance();
    if(inst->tex->textureId != current)
    {
        render();
        current = inst->tex->textureId;
    }
    if(current_program != texture_program)
    {
        render();
        bind(texture_program);
    }
    if(cur >= SIZE - 1)
        render();

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

void SpriteBatch::drawQuad(vec2 loc, vec2 size, const Texture &tex)
{
    if(tex.textureId != current)
    {
        render();
        current = tex.textureId;
    }
    if(current_program != texture_program)
    {
        render();
        bind(texture_program);
    }
    if(cur >= SIZE - 1)
        render();

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

void SpriteBatch::drawRect(vec2 loc, vec2 size, col4 _col)
{
    if(cur >= SIZE - 1)
        render();
    if(current_program != color_program)
    {
        render();
        bind(color_program);
    }

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

void SpriteBatch::drawLine(vec2 start, vec2 end, col4 color)
{

}

void SpriteBatch::render()
{
    if(cur == 0)
        return;
    glEnable(GL_BLEND);
    bind(current_program);

    m_parent->glBindBuffer(GL_ARRAY_BUFFER, vert_b.bufferId());
    m_parent->glBufferData(GL_ARRAY_BUFFER, sizeof(vec3)*cur*4, &pos[0], GL_STREAM_DRAW);
    m_parent->glEnableVertexAttribArray(PROGRAM_VERTEX_ATTRIBUTE);
    m_parent->glVertexAttribPointer(PROGRAM_VERTEX_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, sizeof(vec3), 0);

    m_parent->glBindBuffer(GL_ARRAY_BUFFER, col_b.bufferId());
    m_parent->glBufferData(GL_ARRAY_BUFFER, sizeof(vec2)*cur*4, &uv[0], GL_STREAM_DRAW);
    m_parent->glEnableVertexAttribArray(PROGRAM_TEXCOORD_ATTRIBUTE);
    m_parent->glVertexAttribPointer(PROGRAM_TEXCOORD_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), 0);

    m_parent->glBindBuffer(GL_ARRAY_BUFFER, uv_b.bufferId());
    m_parent->glBufferData(GL_ARRAY_BUFFER, sizeof(col4)*cur*4, &col[0], GL_STREAM_DRAW);
    m_parent->glEnableVertexAttribArray(PROGRAM_COLOR_ATTRIBUTE);
    m_parent->glVertexAttribPointer(PROGRAM_COLOR_ATTRIBUTE, 4, GL_FLOAT, GL_FALSE, sizeof(col4), 0);

    m_parent->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ind_b.bufferId());
    m_parent->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*cur*6, &index[0], GL_STREAM_DRAW);

    m_parent->glDrawElements(GL_TRIANGLES, cur*6, GL_UNSIGNED_INT, NULL);

    cur = 0;
}

void SpriteBatch::setUniform(QMatrix4x4 mat)
{
    uni = mat;
}
