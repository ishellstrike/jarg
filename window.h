#ifndef WINDOW_H_
#define WINDOW_H_

#include "glwidget.h"
#include <QObject>

class GLWidget;

class Window : public QWidget
{
    Q_OBJECT
public:
    explicit Window();
    ~Window();

private:
    GLWidget* a;

signals:

public slots:

};

#endif // WINDOW_H
