#ifndef WINDOW_H
#define WINDOW_H

#include "glwidget.h"
#include <QObject>

class GLWidget;

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window();

private:
    glWidget* a;

signals:

public slots:

};

#endif // WINDOW_H
