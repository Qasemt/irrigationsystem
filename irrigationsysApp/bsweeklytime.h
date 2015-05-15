#ifndef BSWEEKLYTIME_H
#define BSWEEKLYTIME_H

#include <basebusiness.h>
#include <modelweeklytime.h>

class BsWeeklytime : public baseBusiness
{
public:
    BsWeeklytime();
    ModelWeeklyTime   fromSqlQuery(QSqlQuery query);

    QList<ModelWeeklyTime> FillData();
    bool Update(ModelWeeklyTime value);
    bool Insert(ModelWeeklyTime value);
    bool RemoveAll ();
    bool RemovebyId (int id);
};

#endif // BSWEEKLYTIME_H
