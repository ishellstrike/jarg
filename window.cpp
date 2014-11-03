#include "window.h"
#include "jscript.h"
#include "itemdatabase.h"
#include "blockdatabase.h"
#include "jatlas.h"
#include "sector.h"
#include <QList>

Window::Window(QScreen *screen) :
    QWindow(screen)
{
    JScript::instance();

    ItemDataBase::instance()->RegisterApi();
    ItemDataBase::instance()->name("apiapiapi");

    BlockDataBase::instance()->RegisterApi();

    BlockDataBase::instance()->load();
    ItemDataBase::instance()->load();
    JAtlas::instance(this)->load();

    this->resize(500,500);

    setSurfaceType(OpenGLSurface);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setMajorVersion(3);
    format.setMinorVersion(2);
    format.setSamples(4);
    format.setProfile(QSurfaceFormat::CoreProfile );
    setFormat(format);
    create();

    m_context = new QOpenGLContext;
    m_context->setFormat(format);
    bool native = m_context->create();
    qDebug() << "Native context created:" << native;
    m_context->makeCurrent(this);

//    QList<QByteArray> extensions = m_context->extensions().toList();
//    qDebug() << "Supported extensions (" << extensions.count() << ")";
//    for ( const QByteArray extension : extensions )
//        qDebug() << extension;

    m_funcs = m_context->versionFunctions<JGraphics>();
    if (!m_funcs) {
        qWarning() << "Could not obtain OpenGL versions object" << typeid(JGraphics).name();
        exit(1);
    } else
        qDebug() << typeid(JGraphics).name() << "loaded";
    m_funcs->initializeOpenGLFunctions();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(renderNow()));
    //timer->start(100);

    batch = new SpriteBatch(m_funcs, m_context);
    m_animating = true;
    renderLater();


    m_timeMonitor = new QOpenGLTimeMonitor(this);
    m_timeMonitor->setSampleCount(3);
    if ( !m_timeMonitor->create() )
            qWarning() << "Failed to create timer query object";
}

void Window::render()
{
    glClearColor(0.1,0.3,0.5,1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glOrtho(0,1,1,0,0,1);
    glBegin(GL_TRIANGLES);
    glColor3f(1,1,1);
    glVertex2d(0,0);
    glVertex2d(1,0);
    glVertex2d(1,1);
    glEnd();
    batch->DrawRect(vec2(-5,-5), vec2(10,10), Qt::white);
    batch->Render();
}

bool Window::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::UpdateRequest:
        m_update_pending = false;
        renderNow();
        return true;
    default:
        return QWindow::event(event);
    }
}

void Window::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);

    if (isExposed())
        renderNow();
}

void Window::renderNow()
{
    if (!isExposed())
        return;

    m_context->makeCurrent(this);

    m_timeMonitor->recordSample();

    render();

    m_timeMonitor->recordSample();
    m_timeMonitor->waitForSamples();
    auto times = m_timeMonitor->waitForIntervals();
    last_frame = times[0] / 1.0e6;
    m_timeMonitor->reset();

    m_context->swapBuffers(this);

    //qDebug() << last_frame;

    if (m_animating)
        renderLater();
}

void Window::initialize()
{
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "data/shaders/simple.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "data/shaders/simple.frag");
    m_program->link();
    qDebug() << m_program->attributeLocation("qt_Vertex");
    qDebug() << m_program->attributeLocation("qt_MultiTexCoord0");
}

void Window::renderLater()
{
    if (!m_update_pending)
    {
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

void Window::setAnimating(bool animating)
{
    m_animating = animating;
    if(animating)
    {
        renderLater();
    }
}

void Window::resizeEvent(QResizeEvent *event)
{
    int w = event->size().width();
    int h = event->size().height();
    const qreal retinaScale = devicePixelRatio();
    resizeGL(w*retinaScale, h*retinaScale);
    renderNow();
    QWindow::resizeEvent(event);
}

void Window::resizeGL(int w, int h)
{
    if(h == 0)
        h = 1;
    glViewport(0, 0, w, h);
    m_projection.setToIdentity();
    m_projection.perspective(45, (float)w/float(h), 1, 1000);
    m_modelView.setToIdentity();
}

void Window::keyPressEvent(QKeyEvent *event)
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
    QWindow::keyPressEvent(event);
}

Window::~Window()
{
    ItemDataBase::drop();
    BlockDataBase::drop();
    JScript::drop();
    JAtlas::drop();

    delete batch;
}
