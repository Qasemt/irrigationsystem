#ifndef BSCUSTOMTIME_H
#define BSCUSTOMTIME_H
#include <modelcustomtime.h>
#include <basebusiness.h>

class BsCustomTime:baseBusiness
{

public:
    BsCustomTime();
    ModelCustomTime   fromSqlQuery(QSqlQuery query);

    QList<ModelCustomTime> FillData();
    bool Update(ModelCustomTime value);
    bool Insert(ModelCustomTime value);
    bool RemoveAll ();
    bool Removebyid (int id);
    ModelCustomTime FillbyCode(int code);

    QList<ModelCustomTime> FillDatabyCode(int code);
    bool ResetTask();
};

#endif // BSCUSTOMTIME_H
