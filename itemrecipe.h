#ifndef RECIPE_H
#define RECIPE_H

#include <QObject>
#include <QVector>
#include "itemdata.h"
#include <QString>
#include <QScriptValue>
#include <QScriptContext>

class Recipe : public QObject
{
    Q_OBJECT
    QString m_name;
    QString m_description;
    QString m_id;

public:
    Recipe();
    Recipe &operator=(const Recipe &val);
    Recipe(const Recipe &val);

    QVector<Flag> exact_items;
    QVector<RPart> flag_items;
    QVector<Flag> result;
    QVector<Flag> reqire;


    Q_PROPERTY(QString name READ name WRITE name)
    Q_PROPERTY(QString description READ description WRITE description)
    Q_PROPERTY(QString id READ id WRITE id)


    QString name() const
    {
        return m_name;
    }

    QString description() const
    {
        return m_description;
    }

    QString id() const
    {
        return m_id;
    }

signals:

public slots:
    void addExact(QString name, int count);
    void addResult(QString name, int count);
    void addRequire(QString name, int count);
    void addFlag(QString name, int count, int quality);

    void name(QString arg)
    {
        m_name = arg;
    }
    void description(QString arg)
    {
        m_description = arg;
    }
    void id(QString arg)
    {
        m_id = arg;
    }
};

#endif // RECIPE_H
