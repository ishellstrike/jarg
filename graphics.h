#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <QGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_2_Core>
#include <QtOpenGL>

typedef QOpenGLFunctions_3_2_Core JGraphics;
typedef QVector2D vec2;
typedef QVector3D vec3;
typedef QVector4D vec4;
#define STRINGIFY(x) #x
#define STRINGIFYMACRO(y) STRINGIFY(y)
#define INCLUDIFY(x) <##x##>
#define INCLUDIFYMACRO(y) INCLUDIFY(y)


#endif // GRAPHICS_H
