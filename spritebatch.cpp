#include "spritebatch.h"
#include <QGLFunctions>


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

    QGLShader *vshader = new QGLShader(QGLShader::Vertex, m_context);
    const char *vsrc =
        "#version 330 core\n"
        "attribute highp vec4 vertex;\n"
        "attribute mediump vec4 texCoord;\n"
        "attribute mediump vec4 color;\n"
        "varying mediump vec4 texc;\n"
        "varying mediump vec4 col;\n"
        "uniform mediump mat4 matrix;\n"
        "void main(void)\n"
        "{\n"
        "    gl_Position = matrix * vertex;\n"
        "    texc = texCoord;\n"
        "    col = color;\n"
        "}\n";
    vshader->compileSourceCode(vsrc);

    QGLShader *fshader = new QGLShader(QGLShader::Fragment, m_context);
    const char *fsrc =
        "#version 330 core\n"
        "uniform sampler2D texture;\n"
        "varying mediump vec4 texc;\n"
        "varying mediump vec4 col;\n"
        "void main(void)\n"
        "{\n"
        "    gl_FragColor = texture2D(texture, texc.st);\n"
        "}\n";
    fshader->compileSourceCode(fsrc);

    program = new QGLShaderProgram(m_context);
    program->addShader(vshader);
    program->addShader(fshader);
    program->bindAttributeLocation("vertex", PROGRAM_VERTEX_ATTRIBUTE);
    program->bindAttributeLocation("texCoord", PROGRAM_TEXCOORD_ATTRIBUTE);
    program->bindAttributeLocation("color", PROGRAM_COLOR_ATTRIBUTE);
    program->link();

    program->bind();
    program->setUniformValue("texture", 0);

    delete vshader;
    delete fshader;
}

SpriteBatch::~SpriteBatch()
{
    delete[] index;
    delete[] uv;
    delete[] pos;
    delete[] col;

    vert_b.release();
    col_b.release();
    uv_b.release();
    ind_b.release();
    vao.release();
}

void SpriteBatch::DrawQuad(QVector2D loc, QVector2D size, const JTexture &tex)
{
    if(tex.id != current)
    {
        Render();
        current = tex.id;
    }
    if(cur >= SIZE - 1)
        Render();

    pos[cur*4]     = QVector3D(loc.x(), 0, loc.y());
    pos[cur*4 + 1] = QVector3D(loc.x() + size.x(), 0, loc.y());
    pos[cur*4 + 2] = QVector3D(loc.x() + size.x(), 0, loc.y() + size.y());
    pos[cur*4 + 3] = QVector3D(loc.x(), 0, loc.y() + size.y());

    col[cur*4]     = Qt::white;
    col[cur*4 + 1] = Qt::white;
    col[cur*4 + 2] = Qt::white;
    col[cur*4 + 3] = Qt::white;

    uv[cur*4]      = QVector2D(0,0);
    uv[cur*4 + 1]  = QVector2D(1,0);
    uv[cur*4 + 2]  = QVector2D(1,1);
    uv[cur*4 + 3]  = QVector2D(0,1);

    index[cur*6]     = cur*4;
    index[cur*6 + 1] = cur*4 + 1;
    index[cur*6 + 1] = cur*4 + 3;
    index[cur*6 + 1] = cur*4 + 1;
    index[cur*6 + 1] = cur*4 + 2;
    index[cur*6 + 1] = cur*4 + 3;

    cur++;
}

void SpriteBatch::DrawRect(QVector2D loc, QVector2D size, QColor _col)
{
    if(cur >= SIZE - 1)
        Render();

    pos[cur*4]     = QVector3D(loc.x(), 0, loc.y());
    pos[cur*4 + 1] = QVector3D(loc.x() + size.x(), 0, loc.y());
    pos[cur*4 + 2] = QVector3D(loc.x() + size.x(), 0, loc.y() + size.y());
    pos[cur*4 + 3] = QVector3D(loc.x(), 0, loc.y() + size.y());

    col[cur*4]     = _col;
    col[cur*4 + 1] = _col;
    col[cur*4 + 2] = _col;
    col[cur*4 + 3] = _col;

    uv[cur*4]      = QVector2D(0,0);
    uv[cur*4 + 1]  = QVector2D(1,0);
    uv[cur*4 + 2]  = QVector2D(1,1);
    uv[cur*4 + 3]  = QVector2D(0,1);

    index[cur*6]     = cur*4;
    index[cur*6 + 1] = cur*4 + 1;
    index[cur*6 + 1] = cur*4 + 3;
    index[cur*6 + 1] = cur*4 + 1;
    index[cur*6 + 1] = cur*4 + 2;
    index[cur*6 + 1] = cur*4 + 3;

    cur++;
}

void SpriteBatch::Render()
{
   m_parent->glDisable(GL_DEPTH_TEST);
   m_parent->glEnable(GL_BLEND);
   m_parent->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glLoadIdentity();
   if(cur == 0) {
   return;
   }
   vao.bind();
   program->bind();

   m_parent->glBindBuffer(GL_ARRAY_BUFFER, vert_b.bufferId());
   m_parent->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector3D)*cur*4, pos, GL_STREAM_DRAW);
   m_parent->glEnableVertexAttribArray(PROGRAM_VERTEX_ATTRIBUTE);
   m_parent->glVertexAttribPointer(PROGRAM_VERTEX_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), 0);

   m_parent->glBindBuffer(GL_ARRAY_BUFFER, col_b.bufferId());
   m_parent->glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D)*cur*4, uv, GL_STREAM_DRAW);
   m_parent->glEnableVertexAttribArray(PROGRAM_TEXCOORD_ATTRIBUTE);
   m_parent->glVertexAttribPointer(PROGRAM_TEXCOORD_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, sizeof(QVector2D), 0);

   m_parent->glBindBuffer(GL_ARRAY_BUFFER, uv_b.bufferId());
   m_parent->glBufferData(GL_ARRAY_BUFFER, sizeof(QColor)*cur*4, col, GL_STREAM_DRAW);
   m_parent->glEnableVertexAttribArray(PROGRAM_COLOR_ATTRIBUTE);
   m_parent->glVertexAttribPointer(PROGRAM_COLOR_ATTRIBUTE, 4, GL_FLOAT, GL_FALSE, sizeof(QColor), 0);

   m_parent->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ind_b.bufferId());
   m_parent->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*cur*6, index, GL_STREAM_DRAW);

   m_parent->glDrawElements(GL_TRIANGLES, cur*6, GL_UNSIGNED_INT, index);

   cur = 0;
}
