#include "bscustomtime.h"

BsCustomTime::BsCustomTime()
{

}

ModelCustomTime BsCustomTime::fromSqlQuery(QSqlQuery query)
{
    ModelCustomTime mdl ;
    mdl.setId(query.value(query.record().indexOf("id")).toInt());
    mdl.setDevicecode(query.value(query.record().indexOf("devicecode")).toInt());
    mdl.setStarttime(query.value(query.record().indexOf("starttime")).toDateTime());
    mdl.setEnddate(query.value(query.record().indexOf("enddate")).toDateTime());
    mdl.setDurationofsecond(query.value(query.record().indexOf("durationofsecond")).toInt());
    mdl.setDurationofminute(query.value(query.record().indexOf("durationofminute")).toInt());
    mdl.setSmsalert(query.value(query.record().indexOf("smsalert")).toBool());

    return mdl;
}

QList<ModelCustomTime> BsCustomTime::FillData()
{
    QSqlQuery   query;
    QList<ModelCustomTime> tmplist;
    query=  baseBusiness::FillData();
    while (query.next())
    {
        ModelCustomTime md= fromSqlQuery(query);
        tmplist.append(md);
    }
    return tmplist;
}

bool BsCustomTime::Update(ModelCustomTime value)
{
    QMap<QString,QVariant> m;
    m.insert(":devicecode",value.devicecode());
    m.insert(":starttime",value.starttime());
    m.insert(":enddate",value.enddate());
    m.insert(":durationofsecond",value.durationofsecond());
    m.insert(":durationofminute",value.durationofminute());
    m.insert(":smsalert",value.smsalert());

    QString where = QString("id=%1").arg(value.id());
    bool result=    baseBusiness::Update(m,where);
    return result;
}

bool BsCustomTime::Insert(ModelCustomTime value)
{
    QMap<QString,QVariant> m;
    m.insert(":devicecode",value.devicecode());
    m.insert(":starttime",value.starttime());
    m.insert(":enddate",value.enddate());
    m.insert(":durationofsecond",value.durationofsecond());
    m.insert(":durationofminute",value.durationofminute());
    m.insert(":smsalert",value.smsalert());
    bool result=  baseBusiness::Insert(m);
    return result;
}

bool BsCustomTime::RemoveAll()
{
      return  baseBusiness::RemoveAll();
}

bool BsCustomTime::Removebyid(int id)
{
      return  baseBusiness::RemovebyId(id);
}
