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
    QVector<RPart> exact_items;
    QVector<RPart> flag_items;
    QVector<Flag> result;
    QString name;
    QString description;
    QVector<Flag> reqire;

signals:

public slots:

};

#endif // RECIPE_H
