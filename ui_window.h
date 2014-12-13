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
    vec2 drag_point = vec2(0,0);
    bool closing = false;
    col4 color = col4(1,1,1,1);
    col4 second_color = col4(0.5,0.5,0.5,1);
    bool nogui = false;
    void render(abstract_engine &eng);
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
