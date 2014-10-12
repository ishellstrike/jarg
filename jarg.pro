QT           += opengl widgets network script core
CONFIG       += c++14

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
    jscript.h \
    japi.h
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
    jscript.cpp \
    japi.cpp

OTHER_FILES += \
    test.js
