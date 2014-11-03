#include "jatlas.h"
#include <QtOpenGL>
#include <QRectF>
#include <QStringRef>
#include <QDebug>
#define size 2048

void JAtlas::load(QOpenGLContext *context)
{
    QDir items_dir = QDir::current();
    items_dir.cd("data/textures");
    qDebug() << "atlas loading...";
    QStringList files = items_dir.entryList(QStringList("*.png"));
    int i = 0;
    int wi = size/32;
    sSize = QVector2D((32.0)/size, (32.0)/size);
    for(QString s : files)
    {
        QString ss = items_dir.path() + "/" + s;
        QImage temp(ss);

        QPainter painter;
        painter.begin(image);
        painter.drawImage((int)((i%wi)*32), (int)((i/wi)*32), temp);
        painter.end();

        QString ref = s.mid(0, s.length() - (s.length() - s.lastIndexOf('.')));
        sources.insert(ref, QVector2D(((i%wi)*32.0)/size, ((i/wi)*32.0)/size));

        i++;
    }

    tex = new Texture();
    tex->Load(image);

    qDebug() << i << "block textures loaded, id" << tex->textureId;
}

JAtlas::JAtlas(QObject *parent) :
    QObject(parent)
{
    image = new QImage(size, size, QImage::Format_RGBA8888);
}

JAtlas::~JAtlas()
{
    delete image;
    delete tex;
}

JAtlas *JAtlas::m_inst = nullptr;
