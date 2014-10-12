#ifndef BLOCKDATABASE_H
#define BLOCKDATABASE_H
#include "blockdata.h"
#include <unordered_map>
#include <vector>
#include <QJsonObject>

class BlockDataBase : public QObject
{
        Q_OBJECT
public:
        static BlockDataBase &Instance()
        {
                static BlockDataBase theSingleInstance;
                return theSingleInstance;
        }

        QMap<QString, BlockData> data;

        void load();

private:
        BlockDataBase();
        BlockDataBase(const BlockDataBase &root);
        BlockDataBase& operator=(const BlockDataBase &);

        void write(QJsonObject &json);
};

#endif // BLOCKDATABASE_H
