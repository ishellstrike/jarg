#include "jtexture.h"
#include <QtOpenGL>

Texture::Texture() :
    textureId(0),
    name("empty"),
    height(0),
    width(0),
    zsize(0)
{
}

Texture::Texture(GLuint id) :
    textureId(id),
    height(0),
    width(0),
    zsize(0)
{
    QString s = "fromID ";
    name = s.append(id);
}

Texture::~Texture()
{
    if(textureId != -1){
        glDeleteTextures(1, &textureId);
        textureId = -1;
    }
}

void Texture::Load(QImage *image, bool smooth /*= false*/, bool mip /*= false*/)
{
    name = "pixmap";

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->width(), image->height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image->bits());
    if(smooth)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    height = image->height();
    width = image->width();
}

void Texture::Empty(vec2 size, GLuint dim /*= GL_TEXTURE_2D*/, GLuint format /*= GL_RGBA*/)
{
    width = size.x();
    height = size.y();
    name = "empty_texture";

    glGenTextures(1, &textureId);
    glBindTexture(dim, textureId);
    glTexImage2D(dim, 0, format, size.x(), size.y(), 0, format, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(dim, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(dim, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBindTexture(dim, 0);
}

void Texture::EmptyFloatSpace(vec3 size, GLuint dim /*= GL_TEXTURE_2D*/, GLuint color /* = GL_RGB16F*/)
{
//    width = size.x();
//    height = size.y();
//    zsize = size.z();

//    name = "empty_float_space_texture";

//    glGenTextures(1, &textureId);
//    glBindTexture(dim, textureId);

//    glTexParameteri(dim, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(dim, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//    glTexParameteri(dim, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//    if(dim == GL_TEXTURE_2D || dim == GL_TEXTURE_3D)
//        glTexParameteri(dim, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//        if(dim == GL_TEXTURE_3D)
//            glTexParameteri(dim, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

//    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
//    if(dim == GL_TEXTURE_2D)
//    glTexImage2D(GL_TEXTURE_2D, 0, color, width, height, 0, GL_RGB, GL_FLOAT, NULL);
//    else if(dim == GL_TEXTURE_3D)
//        glTexImage3D(GL_TEXTURE_3D, 0, color, width, height, zsize, 0, GL_RGB, GL_FLOAT, NULL);
//        else if(dim == GL_TEXTURE_1D)
//            glTexImage1D(GL_TEXTURE_1D, 0, color, width, 0, GL_RGB, GL_FLOAT, NULL);
}

void Texture::CreateDepth(vec2 size)
{
    width = size.x();
    height = size.y();
    name = "empty_depth";

    glGenTextures(1, &textureId);

    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);

    glBindTexture(GL_TEXTURE_2D, 0);
}


void Texture::Load(const QString &a, bool smooth/* = false*/, bool mip/* = false*/)
{
    name = a;

    QImage image(name);
    image = image.convertToFormat(QImage::Format_RGBA8888);
    image = image.mirrored();

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
    if(smooth)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    height = image.height();
    width = image.width();
}

