QT           += opengl widgets network script core
CONFIG       += c++11

unix: LIBS += -lfreetype

TARGET = jarg
CONFIG   += qt
TEMPLATE = app

INCLUDEPATH += /usr/include/freetype2

HEADERS       = \
    jlogger.h \
    block.h \
    object.h \
    item.h \
    creature.h \
    blockdata.h \
    blockdatabase.h \
    QJsonExtension.h \
    itemdata.h \
    itemdatabase.h \
    jscript.h \
    japi.h \
    itemgroup.h \
    itemrecipe.h \
    sector.h \
    level.h \
    jtexture.h \
    jatlas.h \
    vertex.h \
    levelworker.h \
    sectorlist.h \
    sectorrenderer.h \
    agent.h \
    classicnoise.h \
    parser.h \
    ui_window.h \
    ui_container.h \
    ui_button.h \
    jmath.h \
    ui_label.h \
    settings.h \
    glwidget.h

SOURCES       = main.cpp \
    block.cpp \
    object.cpp \
    item.cpp \
    creature.cpp \
    blockdata.cpp \
    blockdatabase.cpp \
    itemdata.cpp \
    itemdatabase.cpp \
    jscript.cpp \
    japi.cpp \
    itemgroup.cpp \
    itemrecipe.cpp \
    sector.cpp \
    level.cpp \
    jtexture.cpp \
    jatlas.cpp \
    vertex.cpp \
    levelworker.cpp \
    sectorlist.cpp \
    settings.cpp \
    sectorrenderer.cpp \
    agent.cpp \
    classicnoise.cpp \
    ui_window.cpp \
    ui_container.cpp \
    ui_button.cpp \
    ui_label.cpp \
    settings.cpp \
    glwidget.cpp

OTHER_FILES += \
    test.js \
    data/json/items/basic.json \
    data/json/items/aaa.json \
    data/js/items/test.js \
    data/js/items/error.js \
    data/json/items/test_recipe.json \
    data/js/recipes/resipe.js \
    data/js/items/test2.js \
    data/js/blocks/test.js \
    data/js/blocks/error.js \
    simple.vert \
    data/shaders/simple.frag \
    data/shaders/simple.vert \
    data/shaders/color.frag \
    data/shaders/color.vert \
    data/fonts/Inconsolata.otf \
    data/shaders/font.frag \
    data/shaders/font.vert

message($${CONFIG})
