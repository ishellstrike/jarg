#include "window.h"
#include "jscript.h"
#include "itemdatabase.h"
#include "blockdatabase.h"
#include "jatlas.h"
#include "sector.h"
#include <QList>

MainWindow::MainWindow(QScreen *screen) :
    QWindow(screen)
{
    JScript::instance();

    ItemDataBase::instance()->RegisterApi();
    ItemDataBase::instance()->name("apiapiapi");

    BlockDataBase::instance()->RegisterApi();

    BlockDataBase::instance()->load();
    ItemDataBase::instance()->load();

    this->resize(500,500);

    setSurfaceType(OpenGLSurface);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setMajorVersion(2);
    format.setMinorVersion(1);
    format.setSamples(4);
    format.setProfile(QSurfaceFormat::CompatibilityProfile);
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

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), SLOT(renderNow()));
    //timer->start(100);

    batch = new SpriteBatch(m_funcs, m_context);
    drawer = batch;
    m_animating = true;
    renderLater();

    JAtlas::instance(this)->load(m_context);

    m_timeMonitor = new QOpenGLTimeMonitor();
    m_timeMonitor->setSampleCount(3);
    if ( !m_timeMonitor->create() )
            qWarning() << "Failed to create timer query object";
}

void MainWindow::render()
{
    m_funcs->glClearColor(0.2,0.3,0.4,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_program->bind();
    m_modelView.setToIdentity();
    m_modelView.translate(-1.5f, 0.0f, -6.0f);
    m_program->setUniformValue("MVP", m_projection * m_modelView);

    //m_modelView.setToIdentity();
    m_program->setUniformValue("MVP", m_projection * m_modelView);

    batch->setUniform(m_projection * m_modelView);
    batch->drawQuadAtlas(vec2(0,0), vec2(200,200), "error");
    batch->drawRect(vec2(10,10), vec2(100,100), Qt::white);
    batch->render();
    m_program->release();
}


bool MainWindow::event(QEvent *event)
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

void MainWindow::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);

    if (isExposed())
        renderNow();
}

void MainWindow::renderNow()
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

void MainWindow::initialize()
{
    m_program = new QOpenGLShaderProgram();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "data/shaders/simple.vert");
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "data/shaders/simple.frag");
    m_program->link();

   m_funcs->glGenBuffers(2, &m_vboIds[0]);
   GLfloat triangleVertices[] = {
   0.0f, 1.0f, 0.0f,
   -1.0f,-1.0f, 0.0f,
   1.0f,-1.0f, 0.0f,
   };
   m_funcs->glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[0]);
   m_funcs->glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);
   GLfloat quadVertices[] = {
   1.0f, 1.0f, 0.0f,
   -1.0f, 1.0f, 0.0f,
   1.0f,-1.0f, 0.0f,
   -1.0f,-1.0f, 0.0f
   };
   m_funcs->glBindBuffer(GL_ARRAY_BUFFER, m_vboIds[1]);
   m_funcs->glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
}

void MainWindow::renderLater()
{
    if (!m_update_pending)
    {
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

void MainWindow::setAnimating(bool animating)
{
    m_animating = animating;
    if(animating)
    {
        renderLater();
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    int w = event->size().width();
    int h = event->size().height();
    const qreal retinaScale = devicePixelRatio();
    resizeGL(w*retinaScale, h*retinaScale);
    renderNow();
    QWindow::resizeEvent(event);
}

void MainWindow::resizeGL(int w, int h)
{
    if(h == 0)
        h = 1;
    m_w = w;
    m_h = h;
    glViewport(0, 0, w, h);
    m_projection.setToIdentity();
    m_projection.ortho(0,w,h,0,0.1,100);//.perspective(45, (float)w/float(h), 1, 1000);
    m_modelView.setToIdentity();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
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

MainWindow::~MainWindow()
{
    ItemDataBase::drop();
    BlockDataBase::drop();
    JScript::drop();
    JAtlas::drop();

    delete batch;
    delete m_program;
    delete timer;
    delete m_timeMonitor;
}

abstract_engine *MainWindow::drawer = nullptr;
