#ifndef UI_LABEL_H
#define UI_LABEL_H

#include "ui_container.h"
#include <QObject>

class ui_label : public ui_element
{
    Q_OBJECT
public:
    explicit ui_label(ui_container *parent = 0);
    ui_label (ui_label *copy);

    void render(abstract_engine &eng);
    void update();

    QString text;

public slots:
    void keyEvent(QKeyEvent *key);
    void mousePress(QMouseEvent *mouse);
    void mouseRelease(QMouseEvent *mouse);
    void mouseDoubleClick(QMouseEvent *mouse);
    void mouseMove(QMouseEvent *mouse);

signals:
    void onPress();
};

class ui_double_label : public ui_label
{
    Q_OBJECT
public:
    explicit ui_double_label(ui_container *parent = 0);
    ui_double_label (ui_double_label *copy);

    void render(abstract_engine &eng);
    void update();

    QString text;
    QString text2;

signals:
    void onPress();
};

#endif // UI_LABEL_H
