#ifndef RECIPE_H
#define RECIPE_H

#include <QObject>
#include <QVector>
#include <itemdata.h>
#include <QString>

class Recipe : public QObject
{
    Q_OBJECT
public:
    explicit Recipe(QObject *parent = 0);
    QVector<Flag> exact_tools;
    QVector<Flag> exact_items;
    QVector<Flag> flag_items;
    QVector<Flag> flag_tools;
    QVector<Flag> result;
    QString name;
    QString desxription;
    QVector<Flag> reqire;

signals:

public slots:

};

#endif // RECIPE_H
