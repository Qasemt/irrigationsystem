#include "bsmodeldailytime.h"

BsModelDailyTime::BsModelDailyTime()
{
    _TableName ="dailytime";
}

ModelDailyTime BsModelDailyTime::fromSqlQuery(QSqlQuery query)
{
    ModelDailyTime mdl ;
    mdl.setId(query.value(query.record().indexOf("id")).toInt());
    mdl.setDevicecode(query.value(query.record().indexOf("devicecode")).toInt());
    mdl.setStarttime(query.value(query.record().indexOf("starttime")).toDateTime());
    mdl.setEnddate(query.value(query.record().indexOf("enddate")).toDateTime());
    mdl.setDurationofsecond(query.value(query.record().indexOf("durationofsecond")).toInt());
    mdl.setDurationofminute(query.value(query.record().indexOf("durationofminute")).toInt());
    mdl.setSmsalert(query.value(query.record().indexOf("smsalert")).toBool());

    return mdl;
}

QList<ModelDailyTime> BsModelDailyTime::FillData()
{
    QSqlQuery   query;
    QList<ModelDailyTime> tmplist;
    query=  baseBusiness::FillData();
    while (query.next())
    {
        ModelDailyTime md= fromSqlQuery(query);
        tmplist.append(md);
    }


    return tmplist;

}

bool BsModelDailyTime::Update(ModelDailyTime value)
{

    QMap<QString,QVariant> m;
    m.insert(":devicecode",value.devicecode());
    m.insert(":starttime",value.starttime());
    m.insert(":enddate",value.enddate());
    m.insert(":durationofsecond",value.durationofsecond());
    m.insert(":durationofminute",value.durationofminute());
    m.insert(":smsalert",value.smsalert());

    QString where = QString("id=%1").arg(value.id());
    bool result=      baseBusiness::Update(m,where);
    return result;
}

bool BsModelDailyTime::Insert(ModelDailyTime value)
{

    QMap<QString,QVariant> m;
    m.insert(":devicecode",value.devicecode());
    m.insert(":starttime",value.starttime());
    m.insert(":enddate",value.enddate());
    m.insert(":durationofsecond",value.durationofsecond());
    m.insert(":durationofminute",value.durationofminute());
    m.insert(":smsalert",value.smsalert());
    bool result=      baseBusiness::Insert(m);




    return result;
}

bool BsModelDailyTime::RemoveAll()
{
    return  baseBusiness::RemoveAll();
}

bool BsModelDailyTime::RemovebyId(int id)
{
    return  baseBusiness::RemovebyId(id);
}
