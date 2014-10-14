#include "jtexture.h"
#include <QtOpenGL>

JTexture::JTexture(const QString &name, QGLWidget &parent)
{
    id = parent.bindTexture(QPixmap(name), GL_TEXTURE_2D);
    owner = &parent;
}

JTexture::~JTexture()
{
    owner->deleteTexture(id);
    id = 0;
}
