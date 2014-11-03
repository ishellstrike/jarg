#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_2_Core>
#include <QtOpenGL>

#define PROGRAM_VERTEX_ATTRIBUTE 0
#define PROGRAM_TEXCOORD_ATTRIBUTE 1
#define PROGRAM_COLOR_ATTRIBUTE 2

typedef QOpenGLFunctions_3_2_Core JGraphics;
typedef QVector2D vec2;
typedef QVector3D vec3;
typedef QVector4D vec4;
#define STRINGIFY(x) #x
#define STRINGIFYMACRO(y) STRINGIFY(y)
#define INCLUDIFY(x) <##x##>
#define INCLUDIFYMACRO(y) INCLUDIFY(y)

inline void loadShader(char *name_ver, char *name_frag, QOpenGLShaderProgram *program)
{
    if(program->addShaderFromSourceFile(QOpenGLShader::Vertex, name_ver))
        qDebug() << name_ver << "OK";
    if(program->addShaderFromSourceFile(QOpenGLShader::Fragment, name_frag))
        qDebug() << name_frag << "OK";
    if(program->link())
        qDebug() << "link OK";
}


#endif // GRAPHICS_H
