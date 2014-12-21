#include "glwidget.h"
#include "jatlas.h"
#include "blockdatabase.h"
#include "itemdatabase.h"
#include "settings.h"

glwidget::glwidget() :
    QGLWidget()
{

}

glwidget::~glwidget()
{

}

void glwidget::paintGL()
{
    ui->update();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);


    //level->render(batch);

    ui->render(painter);
    painter.end();
    swapBuffers();
}

void glwidget::initializeGL()
{
    //glEnable(GL_MULTISAMPLE);
   // glEnable(GL_BLEND);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(update()));
    timer->start(18);

    JAtlas::instance()->load(this->context());
    BlockDataBase::instance()->load();

    level = new Level(this);
    worker = new LevelWorker(this);
    level->setWorker(worker);

    level->preloadRange(0,0,1);

    ui = new window_system;
    ui->init();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(18);
}

void glwidget::resizeGL(int w, int h)
 {
     if(h == 0)
        h = 1;
     // setup viewport, projection etc.:
     glViewport(0, 0, (GLint)w, (GLint)h);
     glOrtho(0,w,h,0,0,1);

     Settings::instance()->resolution = QSize(w, h);
 }

void glwidget::resizeEvent(QResizeEvent *event)
{
    int w = event->size().width();
    int h = event->size().height();
    const qreal retinaScale = devicePixelRatio();
    resizeGL(w*retinaScale, h*retinaScale);
    //renderNow();
    QWidget::resizeEvent(event);
}

void glwidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_F1:
        {
            m_show_full_screen = !m_show_full_screen;
            if(m_show_full_screen)
                showFullScreen();
            else
                showNormal();
            break;
        }
        case Qt::Key_Escape:
        {
            qApp->exit();
            break;
        }
    }
    QWidget::keyPressEvent(event);
    ui->keyEvent(event);
}

void glwidget::mousePressEvent(QMouseEvent *mouse)
{
    QWidget::mousePressEvent(mouse);
    ui->mousePress(mouse);
}

void glwidget::mouseReleaseEvent(QMouseEvent *mouse)
{
    QWidget::mouseReleaseEvent(mouse);
    ui->mouseRelease(mouse);
}

void glwidget::mouseMoveEvent(QMouseEvent *mouse)
{
    QWidget::mouseMoveEvent(mouse);
    ui->mouseMove(mouse);
}
