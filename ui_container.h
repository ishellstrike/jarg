#ifndef UI_CONTAINER_H
#define UI_CONTAINER_H
#include <QVector>
#include <QObject>
#include "graphics.h"
#include "jtexture.h"

class ui_element : public QObject
{
    Q_OBJECT
public:
    explicit ui_element(ui_element *par = 0);
    ui_element *ui_parent;

    //call automatically via QObject destruction
    ~ui_element();

    vec2 size;

    virtual void render(abstract_engine &eng) = 0;
    virtual void update() = 0;
    vec2 get_position();
    vec2 loc;
};

class ui_container : public ui_element
{
public:
    explicit ui_container(ui_element *par = 0);

    //call automatically via QObject destruction
    ~ui_container();

    QVector<ui_element *> elements;
    void addElement(ui_element *element);
};

#endif // UI_CONTAINER_H
