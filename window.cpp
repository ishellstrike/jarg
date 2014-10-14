#include <QtWidgets>
#include "window.h"
#include "glwidget.h"
#include "jscript.h"
#include "itemdatabase.h"
#include "blockdatabase.h"
#include "jatlas.h"
#include "sector.h"
#include <QtOpenGL>

Window::Window()
{
    JScript::instance();
    ItemDataBase::instance()->RegisterApi();
    ItemDataBase::instance()->name("apiapiapi");
    BlockDataBase::instance()->load();
    ItemDataBase::instance()->load();
    JAtlas::instance(this)->load();

    Sector sec;
    sec.setBlock(0, 0, "error");
    auto t = sec.getBlock(0, 0);

    a = new GLWidget();
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(a, 1, 1);
    setLayout(mainLayout);
    this->resize(500,500);
}

Window::~Window()
{
    ItemDataBase::drop();
    BlockDataBase::drop();
    JScript::drop();
    JAtlas::drop();
}
