#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_2_1>
#include <QtOpenGL>
#include "jtexture.h"
#include "jmath.h"

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1
#define PROGRAM_COLOR_ATTRIBUTE 2

typedef QOpenGLFunctions_2_1 JGraphics;
#define STRINGIFY(x) #x
#define STRINGIFYMACRO(y) STRINGIFY(y)
#define INCLUDIFY(x) <##x##>
#define INCLUDIFYMACRO(y) INCLUDIFY(y)

inline void loadShader(const QString &name_ver, const QString &name_frag, QOpenGLShaderProgram *program)
{
    if(program->addShaderFromSourceFile(QOpenGLShader::Vertex, name_ver))
        qDebug() << name_ver << "OK";
    if(program->addShaderFromSourceFile(QOpenGLShader::Fragment, name_frag))
        qDebug() << name_frag << "OK";
    if(program->link())
        qDebug() << "link OK";
}

class abstract_engine
{
public:
    virtual void drawLine(vec2 loc, vec2 size, float width, col4 col) = 0;
    virtual void drawQuad(vec2 loc, vec2 size, const Texture &tex, vec4 col = WHITE) = 0;
    virtual void drawQuadAtlas(vec2 loc, vec2 size, QString tex, vec4 col = WHITE) = 0;
    virtual void drawRect(vec2 loc, vec2 size, col4 col) = 0;
    virtual void drawRect(vec2 loc, vec2 size, col4 col, col4 col2) = 0;
    virtual void setScissor(vec2 loc, vec2 size) = 0;
    virtual void resetScissor() = 0;
    virtual void render() = 0;
    virtual vec2 drawText(const QString &text, vec2 pos, vec2 size, vec4 col = WHITE) = 0;
};


#endif // GRAPHICS_H
