#include <QtWidgets>
#include "window.h"
#include "glwidget.h"

Window::Window()
{
    a = new GLWidget();
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(a, 1, 1);
    setLayout(mainLayout);
    this->resize(500,500);
}
