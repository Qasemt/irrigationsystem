#include "bseventslog.h"

BsEventsLog::BsEventsLog()
{

}

ModelEventsLog BsEventsLog::fromSqlQuery(QSqlQuery query)
{
    ModelEventsLog mdl ;
    mdl.setId(query.value(query.record().indexOf("id")).toInt());
    mdl.setDevicecode(query.value(query.record().indexOf("devicecode")).toInt());
    mdl.setSchedulemode(query.value(query.record().indexOf("schedulemode")).toInt());
    mdl.setStarttime(query.value(query.record().indexOf("starttime")).toDateTime());
    mdl.setEnddate(query.value(query.record().indexOf("enddate")).toDateTime());
    mdl.setDurationofsecond(query.value(query.record().indexOf("durationofsecond")).toInt());
    mdl.setDurationofminute(query.value(query.record().indexOf("durationofminute")).toInt());
    mdl.setMobilenumber(query.value(query.record().indexOf("mobilenumber")).toString());
    mdl.setTransferstatus(query.value(query.record().indexOf("transferstatus")).toBool());

    return mdl;

}

QList<ModelEventsLog> BsEventsLog::FillData()
{
    QSqlQuery  query;
    QList<ModelEventsLog> tmplist;
    query=  baseBusiness::FillData();
    while (query.next())
    {
        ModelEventsLog md= fromSqlQuery(query);
        tmplist.append(md);
    }


    return tmplist;
}

bool BsEventsLog::Update(ModelEventsLog value)
{
    QMap<QString,QVariant> m;
    m.insert(":devicecode",value.devicecode());
    m.insert(":schedulemode",value.devicecode());
    m.insert(":starttime",value.starttime());
    m.insert(":enddate",value.enddate());
    m.insert(":durationofsecond",value.durationofsecond());
    m.insert(":durationofminute",value.durationofminute());
    m.insert(":mobilenumber",value.mobilenumber());
    m.insert(":transferstatus",value.transferstatus());

    QString where = QString("id=%1").arg(value.id());
    bool result=      baseBusiness::Update(m,where);
    return result;

}

bool BsEventsLog::Insert(ModelEventsLog value)
{
    QMap<QString,QVariant> m;
    m.insert(":devicecode",value.devicecode());
    m.insert(":schedulemode",value.devicecode());
    m.insert(":starttime",value.starttime());
    m.insert(":enddate",value.enddate());
    m.insert(":durationofsecond",value.durationofsecond());
    m.insert(":durationofminute",value.durationofminute());
    m.insert(":mobilenumber",value.mobilenumber());
    m.insert(":transferstatus",value.transferstatus());


    bool result=      baseBusiness::Insert(m);
    return result;
}

bool BsEventsLog::RemoveAll()
{
   return baseBusiness::RemoveAll();
}

bool BsEventsLog::RemovebyId(int id)
{
  return  baseBusiness::RemovebyId(id);
}

