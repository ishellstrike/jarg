QT           += opengl widgets
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
    QJsonExtension.h
SOURCES       = main.cpp \
                window.cpp \
    glwidget.cpp \
    block.cpp \
    object.cpp \
    item.cpp \
    creature.cpp \
    blockdata.cpp \
    blockdatabase.cpp
