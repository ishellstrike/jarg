#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#include "ui_container.h"

#include <QObject>

class ui_button : public QObject, public ui_element
{
    Q_OBJECT
public:
    explicit ui_button(ui_element *parent = 0);

signals:

public slots:


    // ui_element interface
public:
    void render();
    void update();
};

#endif // UI_BUTTON_H
