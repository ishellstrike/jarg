QT           += opengl widgets network script
CONFIG       += c++11

HEADERS       = window.h \
    glwidget.h \
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
    jscript.h
SOURCES       = main.cpp \
                window.cpp \
    glwidget.cpp \
    block.cpp \
    object.cpp \
    item.cpp \
    creature.cpp \
    blockdata.cpp \
    blockdatabase.cpp \
    itemdata.cpp \
    itemdatabase.cpp \
    jscript.cpp

OTHER_FILES += \
    test.js
