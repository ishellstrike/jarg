#include <QtWidgets>
#include "window.h"
#include "glwidget.h"

Window::Window()
{
    a = new glWidget();
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(a, 1, 1);
}
