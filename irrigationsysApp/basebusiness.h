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
    QSqlQuery FillData(QString fields="",QString whereparam="");
    bool Update(QMap<QString,QVariant> params,QString whereparams);
    bool Insert(QMap<QString,QVariant> params);
    bool RemoveAll ();
    bool RemovebyId (int id);

    bool Removebywhere (QString whereparams);

    int numberOfRecords(QSqlQuery q)
    {
        int cnt=0;
        while (q.next()) {
            cnt++;
        }
        return cnt;
    }
};

#endif // BASEBUSINESS_H
