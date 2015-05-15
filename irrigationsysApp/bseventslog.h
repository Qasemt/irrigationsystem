#ifndef BSEVENTSLOG_H
#define BSEVENTSLOG_H

#include <basebusiness.h>
#include <modeleventslog.h>

class BsEventsLog:baseBusiness
{
public:
    BsEventsLog();
    ModelEventsLog   fromSqlQuery(QSqlQuery query);

    QList<ModelEventsLog> FillData();
    bool Update(ModelEventsLog value);
    bool Insert(ModelEventsLog value);
    bool RemoveAll();
    bool RemovebyId(int id);
};

#endif // BSEVENTSLOG_H
