#include "ui_button.h"
#include "ui_window.h"
#include "jmath.h"
#include "settings.h"

void ui_window::create()
{
    loc = QPoint(100, 100);
    size = QSize(200, 200);
    close_b = new ui_close_button(this);
    close_b->loc = QPoint(size.width() - 19 - OUTLINE*1.5, OUTLINE);
    close_b->size = QSize(18, 18);
    close_b->text = "";
    connect(close_b, SIGNAL(onPress()), this, SLOT(close()));
    title = "window";
}

ui_window::ui_window(ui_container *parent) :
    ui_container(parent)
{
    create();
}

void ui_window::render(QPainter &eng)
{
    auto pos = get_position();
    auto set = Settings::instance();
    eng.setPen(set->ui_outline);
    eng.setBrush(QBrush(set->ui_body, Qt::SolidPattern));

    eng.drawRect(QRect(pos, size));
    eng.drawLine(pos + QPoint(0, HEADER), pos + QPoint(size.width(), HEADER));
    eng.drawText(QRect(pos + QPoint(3,0), QSize(size.width(), HEADER)), title);

    for(ui_element *i : elements)
    {
        i->render(eng);
    }
}

void ui_window::mousePress(QMouseEvent *mouse)
{
    auto p = get_position();
    auto m = mouse->pos();
    QRect rect(p, QSize(size.width(), HEADER + OUTLINE*2));
    if(rect.contains(m))
    {
        dragged = true;
        drag_point = QPoint(m.x(), m.y()) - p;
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
        loc  = QPoint(mouse->pos().x(), mouse->pos().y()) - drag_point;
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
   b->loc = QPoint(70, 50);
   b->size = QSize(100,20);
}

