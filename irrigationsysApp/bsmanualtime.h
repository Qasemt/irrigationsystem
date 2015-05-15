#ifndef BSMANUALTIME_H
#define BSMANUALTIME_H

#include <basebusiness.h>
#include <modelmanualtime.h>

class BsManualTime:baseBusiness
{
public:
    BsManualTime();
    ModelManualTime   fromSqlQuery(QSqlQuery query);

    QList<ModelManualTime> FillData();
    bool Update(ModelManualTime value);
    bool Insert(ModelManualTime value);
    bool RemoveAll ();
    bool RemovebyId (int id);
};

#endif // BSMANUALTIME_H
