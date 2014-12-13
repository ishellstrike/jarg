#ifndef UI_CONTAINER_H
#define UI_CONTAINER_H
#include <QVector>
#include <QObject>
#include "graphics.h"
#include "jtexture.h"

class ui_container;

class ui_element : public QObject
{
    Q_OBJECT
public:
    explicit ui_element(ui_container *par = 0);
    ui_container *ui_parent;

    //call automatically via QObject destruction
    ~ui_element();

    vec2 size;
    bool aimed;

    virtual void render(abstract_engine &eng) = 0;
    virtual void update() = 0;
    vec2 get_position();
    vec2 loc;

public slots:
    virtual void keyEvent(QKeyEvent *key) = 0;
    virtual void mousePress(QMouseEvent *mouse) = 0;
    virtual void mouseRelease(QMouseEvent *mouse) = 0;
    virtual void mouseDoubleClick(QMouseEvent *mouse) = 0;
    virtual void mouseMove(QMouseEvent *mouse) = 0;
};

class ui_container : public ui_element
{
    Q_OBJECT

public:
    explicit ui_container(ui_container *par = 0);

    //call automatically via QObject destruction
    ~ui_container();

    QVector<ui_element *> elements;

    void render(abstract_engine &eng);
    void update();
    void addElement(ui_element *element);
public slots:
    void mousePress(QMouseEvent *mouse);
    void mouseRelease(QMouseEvent *mouse);
    void mouseDoubleClick(QMouseEvent *mouse);
    void mouseMove(QMouseEvent *mouse);
    void keyEvent(QKeyEvent *key);
};

#endif // UI_CONTAINER_H
