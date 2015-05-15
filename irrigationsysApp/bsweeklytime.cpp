#include "bsweeklytime.h"

BsWeeklytime::BsWeeklytime()
{
    _TableName="weeklytime";
}

ModelWeeklyTime BsWeeklytime::fromSqlQuery(QSqlQuery query)
{
    ModelWeeklyTime mdl ;
    mdl.setId(query.value(query.record().indexOf("id")).toInt());
    mdl.setDayindex(query.value(query.record().indexOf("dayindex")).toInt());
    mdl.setDevicecode(query.value(query.record().indexOf("devicecode")).toInt());
    mdl.setStarttime(query.value(query.record().indexOf("starttime")).toDateTime());
    mdl.setEnddate(query.value(query.record().indexOf("enddate")).toDateTime());
    mdl.setDurationofsecond(query.value(query.record().indexOf("durationofsecond")).toInt());
    mdl.setDurationofminute(query.value(query.record().indexOf("durationofminute")).toInt());
    mdl.setSmsalert(query.value(query.record().indexOf("smsalert")).toBool());

    return mdl;
}

QList<ModelWeeklyTime> BsWeeklytime::FillData()
{
    QSqlQuery   query;
    QList<ModelWeeklyTime> tmplist;

    query=  baseBusiness::FillData();

    while (query.next())
    {
        ModelWeeklyTime md= fromSqlQuery(query);
        tmplist.append(md);
    }

    return tmplist;
}

bool BsWeeklytime::Update(ModelWeeklyTime value)
{
    QMap<QString,QVariant> m;
    m.insert(":devicecode",value.devicecode());
    m.insert(":dayindex",value.dayindex());
    m.insert(":starttime",value.starttime());
    m.insert(":enddate",value.enddate());
    m.insert(":durationofsecond",value.durationofsecond());
    m.insert(":durationofminute",value.durationofminute());
    m.insert(":smsalert",value.smsalert());

    QString where = QString("id=%1").arg(value.id());
    bool result= baseBusiness::Update(m,where);
    return result;
}

bool BsWeeklytime::Insert(ModelWeeklyTime value)
{
    QMap<QString,QVariant> m;
    m.insert(":devicecode",value.devicecode());
    m.insert(":dayindex",value.dayindex());
    m.insert(":starttime",value.starttime());
    m.insert(":enddate",value.enddate());
    m.insert(":durationofsecond",value.durationofsecond());
    m.insert(":durationofminute",value.durationofminute());
    m.insert(":smsalert",value.smsalert());
    bool result=      baseBusiness::Insert(m);
    return result;
}

bool BsWeeklytime::RemoveAll()
{
    baseBusiness::RemoveAll();

}

bool BsWeeklytime::RemovebyId(int id)
{
    baseBusiness::RemovebyId(id);
}

