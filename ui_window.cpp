#include "ui_button.h"
#include "ui_window.h"
#include "window.h"
#include "graphics_helper.h"

ui_window::ui_window(ui_element *parent) :
    ui_container(parent)
{
    loc = vec2(100, 100);
    size = vec2(200, 200);
}

void ui_window::render(abstract_engine &eng)
{
    auto pos = get_position();
    drawBoxScissor(pos, size, Qt::white, eng);

    for(ui_element *i : elements)
    {
        i->render(eng);
    }
    eng.resetScissor();
}

void ui_window::update()
{
    for(ui_element *i : elements)
    {
        i->update();
    }
}


window_system::window_system() :
    ui_container(0)
{

}

void window_system::render(abstract_engine &eng)
{
    for(ui_element *i : elements)
    {
        i->render(eng);
    }
}

void window_system::update()
{
    for(ui_element *i : elements)
    {
        i->update();
    }
}

void window_system::init()
{
    auto a = new ui_window(this);
    auto b = new ui_button(a);
    b->loc = vec2(70, 50);
    b->size = vec2(200,1000);
    addElement(a);
    a->addElement(b);
}
