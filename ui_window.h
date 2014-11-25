#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include "ui_container.h"

#include <QObject>

class ui_window : public QObject, public ui_container, public ui_element
{
    Q_OBJECT
public:
    explicit ui_window(ui_element *parent = 0);

signals:

public slots:


    // ui_element interface
public:
    void render();
    void update();
};

class window_system : public QObject, public ui_container, public ui_element
{
    Q_OBJECT
public:
    explicit window_system();

    // ui_element interface
public:
    void render();
    void update();

    void init();
};

#endif // UI_WINDOW_H
