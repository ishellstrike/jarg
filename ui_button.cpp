#include "ui_button.h"
#include "settings.h"

ui_button::ui_button(ui_container *parent) :
    ui_element(parent)
{
    size = QSize(50, 20);
}

void ui_button::render(QPainter &eng)
{
    auto pos = get_position();
    auto set = Settings::instance();
    eng.setBrush(QBrush(aimed ? set->ui_body.light() : set->ui_body, Qt::SolidPattern));
    eng.drawRect(QRect(pos, size));
    if(!text.isEmpty())
        eng.drawText(QRect(pos + QPoint(3,0), size), text);
}

void ui_button::update()
{

}

void ui_button::keyEvent(QKeyEvent *key)
{
    Q_UNUSED(key);
}

void ui_button::mousePress(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
    emit onPress();
}

void ui_button::mouseRelease(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
}

void ui_button::mouseDoubleClick(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
}

void ui_button::mouseMove(QMouseEvent *mouse)
{
    Q_UNUSED(mouse);
}


ui_close_button::ui_close_button(ui_container *parent) :
    ui_button(parent)
{

}

void ui_close_button::render(QPainter &eng)
{
    ui_button::render(eng);
    auto p = get_position();
    auto set = Settings::instance();
    eng.drawRect(QRect(p, size));
   // eng.drawLine
    //drawLineEx(p, size - vec2(1, 0), set->ui_outline, eng, 2, 3, vec2(0, 0), vec2(0.5, 0.5), vec2(1, 0));
   // drawLineEx(p, size - vec2(1, 0), set->ui_outline, eng, 2, 3, vec2(0, 1), vec2(0.5, 0.5), vec2(1, 1));
}
