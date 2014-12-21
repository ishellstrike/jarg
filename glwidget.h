#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QObject>
#include "level.h"
#include "ui_window.h"

class glwidget : public QGLWidget
{
    Q_OBJECT
public:
    glwidget();
    ~glwidget();
    void paintGL();
    window_system *ui;
    Level *level;
    LevelWorker *worker;
    void initializeGL();
    void resizeGL(int w, int h);
    bool m_show_full_screen = false;
    QTimer *timer;
public slots:
    void mouseMoveEvent(QMouseEvent *mouse);
    void mouseReleaseEvent(QMouseEvent *mouse);
    void mousePressEvent(QMouseEvent *mouse);
    void keyPressEvent(QKeyEvent *event);
    void resizeEvent(QResizeEvent *event);
};

#endif // GLWIDGET_H
