#ifndef BASEBUSINESS_H
#define BASEBUSINESS_H

#include <QSqlQuery>
#include <qvariant.h>
#include <QList>
#include <datahelper.h>
#include <QSqlRecord>
#include <QMap>
class baseBusiness
{
public:
    baseBusiness();
    QString _TableName;
    QSqlQuery FillData();
    bool Update(QMap<QString,QVariant> params,QString whereparams);
    bool Insert(QMap<QString,QVariant> params);
    bool RemoveAll ();
    bool RemovebyId (int id);

};

#endif // BASEBUSINESS_H
