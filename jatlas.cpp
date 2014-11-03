#include "jatlas.h"
#include <QtOpenGL>
#include <QRectF>
#include <QStringRef>
#include <QDebug>
#define size 2048

void JAtlas::load()
{
    QDir items_dir = QDir::current();
    items_dir.cd("data/textures/blocks");
    QStringList files = items_dir.entryList(QStringList("*.png"));
    int i = 0;
    int wi = size/32;
    for(QString s : files)
    {
        QString ss = items_dir.path() + "/" + s;
        QPixmap temp(ss);

        QPainter painter;
        painter.begin(image);
        painter.drawPixmap((int)((i%wi)*32), (int)((i/wi)*32), temp);
        painter.end();

        QString ref = s.mid(0, s.length() - s.lastIndexOf('.'));
        sources.insert(ref, QVector2D(((i%wi)*32.0)/size, ((i/wi)*32.0)/size));

        i++;
    }
    qDebug() << i << "block textures loaded";
}

JAtlas::JAtlas(QObject *parent) :
    QObject(parent)
{
    image = new QPixmap(size, size);
}

JAtlas::~JAtlas()
{
    delete image;
}

JAtlas *JAtlas::m_inst = nullptr;
