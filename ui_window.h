#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include "ui_button.h"
#include "ui_container.h"

#include <QObject>

class ui_window : public ui_container
{
    Q_OBJECT
    void create();
public:
    explicit ui_window(ui_container *parent = 0);

    bool dragged = false;
    QPoint drag_point = QPoint(0,0);
    bool closing = false;
    QColor color = QColor(1,1,1,1);
    QColor second_color = QColor(0.5,0.5,0.5,1);
    bool nogui = false;
    void render(QPainter &eng);
    ui_close_button *close_b;
    QString title;
public slots:
    void mousePress(QMouseEvent *mouse);
    void mouseRelease(QMouseEvent *mouse);
    void mouseMove(QMouseEvent *mouse);
    void close();
};

class window_system : public ui_container
{
    Q_OBJECT
public:
    explicit window_system();

    void update();

    void init();
};

#endif // UI_WINDOW_H
