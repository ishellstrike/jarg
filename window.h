#ifndef WINDOW_H_
#define WINDOW_H_

#include <QObject>
#include "graphics.h"
#include "spritebatch.h"
#include <QMatrix4x4>

class GameContainer;

class Window : public QWindow
{
    Q_OBJECT
public:
    explicit Window( QScreen* screen );
    ~Window();

    bool m_update_pending;
    bool m_show_full_screen;
    bool m_animating;
    int m_pos_atr, m_uv_atr;

    bool event(QEvent *event);
    void exposeEvent(QExposeEvent *event);
    void render();

    QTimer *timer;

    QOpenGLTimeMonitor *m_timeMonitor;
    SpriteBatch *batch;
    QOpenGLShaderProgram *m_program;

    QMatrix4x4 m_projection;
    QMatrix4x4 m_modelView;

    float last_frame;
    void keyPressEvent(QKeyEvent *event);
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
