#ifndef JTEXTURE_H
#define JTEXTURE_H
#include <QString>
#include <QtOpenGL>

struct Texture {
public:
    GLuint textureId;
    QString name;
    unsigned int height;
    unsigned int width;
    unsigned int zsize;

    Texture();
    Texture(GLuint id);
    ~Texture();

    void Load(const QString &a, bool smooth = false, bool mip = false);
    void Load(QImage *a, bool smooth = false, bool mip = false);
    void Empty(QVector2D size, GLuint dim = GL_TEXTURE_2D, GLuint format = GL_RGBA);
    void CreateDepth(QVector2D size);
    void EmptyFloatSpace(QVector3D size, GLuint dim = GL_TEXTURE_2D, GLuint color = GL_RGB16F);
};

#endif // JTEXTURE_H
