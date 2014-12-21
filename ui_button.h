#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include "ui_container.h"

#include <QObject>

class ui_button : public ui_element
{
    Q_OBJECT
public:
    explicit ui_button(ui_container *parent = 0);
    ui_button (ui_button *copy);

    void render(QPainter &eng);
    void update();
    QString text = "Button";

public slots:
    void keyEvent(QKeyEvent *key);
    void mousePress(QMouseEvent *mouse);
    void mouseRelease(QMouseEvent *mouse);
    void mouseDoubleClick(QMouseEvent *mouse);
    void mouseMove(QMouseEvent *mouse);

signals:
    void onPress();
};

class ui_close_button : public ui_button
{
    Q_OBJECT
public:
    explicit ui_close_button(ui_container *parent = 0);
    void render(QPainter &eng);
};

#endif // UI_BUTTON_H
