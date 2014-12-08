#ifndef WINDOW_H_
#define WINDOW_H_

#include <QObject>
#include "graphics.h"
#include "spritebatch.h"
#include "ui_window.h"
#include <QMatrix4x4>

class GameContainer;

class MainWindow : public QWindow
{
    Q_OBJECT
public:
    explicit MainWindow( QScreen* screen );
    ~MainWindow();

    bool m_update_pending;
    bool m_show_full_screen;
    bool m_animating;
    int m_pos_atr, m_uv_atr;
    uint m_vboIds[2];
    GLfloat *triangleVertices;
    GLfloat *quadVertices;
    int m_w, m_h;

    bool event(QEvent *event);
    void exposeEvent(QExposeEvent *event);
    void render();

    static abstract_engine *drawer;
    static window_system *ui_system;

    QTimer *timer;

    QOpenGLTimeMonitor *m_timeMonitor;
    SpriteBatch *batch;
    QOpenGLShaderProgram *m_program;

    QMatrix4x4 m_projection;
    QMatrix4x4 m_modelView;

    float last_frame;
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *mouse);
    void mouseReleaseEvent(QMouseEvent *mouse);
    void mouseMoveEvent(QMouseEvent *mouse);
    void resizeGL(int w, int h);
    void resizeEvent(QResizeEvent *event);
    void initialize();
    void renderLater();
    void setAnimating(bool animating);
private:
    QOpenGLContext *m_context;
    JGraphics *m_funcs;

signals:

public slots:
    void renderNow();

};

#endif // WINDOW_H
