#ifndef OBJECT_H
#define OBJECT_H
#include <string>
#include <QtOpenGL>

class Object
{
public:
    Object();
    virtual QString id() = 0;
    virtual QString name() = 0;
    virtual QString description() = 0;
};

#endif // OBJECT_H
