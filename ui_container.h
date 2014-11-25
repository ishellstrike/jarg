#ifndef UI_CONTAINER_H
#define UI_CONTAINER_H
#include <QVector>
#include <QObject>
#include "graphics.h"
#include "jtexture.h"

class ui_element
{
public:
    ui_element(ui_element *par = 0);
    ui_element *ui_parent;
    vec2 size;

    virtual void render() = 0;
    virtual void update() = 0;
    vec2 get_position();
private:
    vec2 loc;
};

class ui_container
{
public:
    ui_container();
    ~ui_container();
    QVector<ui_element *> elements;
    void addElement(ui_element * element);
};

#endif // UI_CONTAINER_H
