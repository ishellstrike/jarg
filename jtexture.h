#ifndef JTEXTURE_H
#define JTEXTURE_H
#include <QString>
#include <QtOpenGL>

class JTexture
{
public:
    JTexture(const QString &name, QGLWidget &parent);
    ~JTexture();

    GLuint id;
    QString name;
    QGLWidget *owner;
private:

};

#endif // JTEXTURE_H
