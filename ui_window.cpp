#include "ui_button.h"
#include "ui_window.h"
#include "window.h"
#include "graphics_helper.h"
#include "jmath.h"

void ui_window::create()
{
    loc = vec2(100, 100);
    size = vec2(200, 200);
    close_b = new ui_close_button(this);
    close_b->loc = vec2(size.x() - 18 - OUTLINE*1.5, OUTLINE*1.5);
    close_b->size = vec2(18, 18);
    connect(close_b, SIGNAL(onPress()), this, SLOT(close()));
    title = "window";
}

ui_window::ui_window(ui_container *parent) :
    ui_container(parent)
{
    create();
}

void ui_window::render(abstract_engine &eng)
{
    auto pos = get_position();
    drawBoxOutline(pos, size, color, eng);
    drawBoxScissor(pos, vec2(size.x(), HEADER + OUTLINE*2), color, second_color, eng);
    eng.drawText(title, pos + vec2(OUTLINE, -OUTLINE), vec2(0.33,0.33), BLACK);
    drawBoxScissor(pos + vec2(OUTLINE*2, OUTLINE*2 + HEADER),
                   size - vec2((OUTLINE*2)*2, OUTLINE*4 + HEADER), color, eng);

    /*
     *
     *
     *
     *
     *
     */

    for(ui_element *i : elements)
    {
        i->render(eng);
    }
    eng.resetScissor();
    close_b->render(eng);
    eng.resetScissor();
}

void ui_window::mousePress(QMouseEvent *mouse)
{
    auto p = get_position();
    auto m = mouse->pos();
    auto s = p + vec2(size.x(), HEADER + OUTLINE*2);
    if(m.x() > p.x() && m.y() > p.y() && m.x() < s.x() && m.y() < s.y())
    {
        dragged = true;
        drag_point = vec2(m.x(), m.y()) - p;
    }
    else
        dragged = false;
    ui_container::mousePress(mouse);
}

void ui_window::mouseRelease(QMouseEvent *mouse)
{
    dragged = false;
    ui_container::mouseRelease(mouse);
}

void ui_window::mouseMove(QMouseEvent *mouse)
{
    if (dragged)
        loc  = vec2(mouse->pos().x(), mouse->pos().y()) - drag_point;
    ui_container::mouseMove(mouse);
}

void ui_window::close()
{
    closing = true;
}


window_system::window_system() :
    ui_container(0)
{

}

void window_system::update()
{
    for(int i = 0; i<elements.size(); i++)
    {
       if (((ui_window *)elements[i])->closing)
           elements.removeAt(i);
    }
    ui_container::update();
}

void window_system::init()
{
   auto a = new ui_window(this);
   auto b = new ui_button(a);
   b->loc = vec2(70, 50);
   b->size = vec2(100,20);
}

