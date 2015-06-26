#ifndef BSMODELDAILYTIME_H
#define BSMODELDAILYTIME_H
#include <modeldailytime.h>

#include <QSqlQuery>
#include <qvariant.h>
#include <QList>
#include <datahelper.h>
#include <QSqlRecord>
#include <basebusiness.h>
class BsModelDailyTime:baseBusiness
{
public:
    BsModelDailyTime();
    ModelDailyTime   fromSqlQuery(QSqlQuery query);

    QList<ModelDailyTime> FillData();
    bool Update(ModelDailyTime value);
    bool Insert(ModelDailyTime value);
    bool RemoveAll ();
    bool RemovebyId (int id);
    QList<ModelDailyTime> FillDatabyCode(int code);
    bool ResetTask();
private:

};

#endif // BSMODELDAILYTIME_H
