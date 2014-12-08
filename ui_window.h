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
    explicit ui_window(ui_element *parent = 0);
    ui_window(ui_window *copy);

    bool dragged;
    vec2 drag_point;
    bool closing;
    col4 color;
    col4 second_color;
    void render(abstract_engine &eng);
    ui_close_button *close_b;
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
