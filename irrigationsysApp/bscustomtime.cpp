#include "bscustomtime.h"

BsCustomTime::BsCustomTime()
{
    _TableName="customtime";
}

ModelCustomTime BsCustomTime::fromSqlQuery(QSqlQuery query)
{
    ModelCustomTime mdl ;
    mdl.setId(query.value(query.record().indexOf("id")).toInt());
    mdl.setDevicecode(query.value(query.record().indexOf("devicecode")).toInt());
    mdl.setStarttime(query.value(query.record().indexOf("starttime")).toDateTime());
    mdl.setEndTime(query.value(query.record().indexOf("endtime")).toDateTime());
    mdl.setDurationofsecond(query.value(query.record().indexOf("durationofsecond")).toInt());
    mdl.setDurationofminute(query.value(query.record().indexOf("durationofminute")).toInt());
    mdl.setSmsalert(query.value(query.record().indexOf("smsalert")).toBool());
    mdl.setIsTaskActive(query.value(query.record().indexOf("istaskactive")).toBool());
    return mdl;
}

ModelCustomTime BsCustomTime::FillbyCode(int code)
{
    QSqlQuery   query;
    ModelCustomTime tmp;
    query=  baseBusiness::FillData("*",QString("devicecode=%1").arg(QString::number(code)));
    while (query.next())
    {
        tmp= fromSqlQuery(query);

    }
    return tmp;
}

QList<ModelCustomTime> BsCustomTime::FillDatabyCode(int code)
{
    QSqlQuery   query;
    QList<ModelCustomTime> tmplist;
    query=  baseBusiness::FillData("*",QString("devicecode=%1").arg(QString::number(code)));
    while (query.next())
    {
        ModelCustomTime md= fromSqlQuery(query);
        tmplist.append(md);
    }
    return tmplist;
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
    m.insert(":endtime",value.endtime());
    m.insert(":durationofsecond",value.durationofsecond());
    m.insert(":durationofminute",value.durationofminute());
    m.insert(":smsalert",value.smsalert());
    m.insert(":istaskactive",value.isTaskActive());
    QString where = QString("id=%1").arg(value.id());
    bool result=    baseBusiness::Update(m,where);
    return result;
}
bool BsCustomTime::ResetTask()
{
    QMap<QString,QVariant> m;
    m.insert(":istaskactive",false);
    bool result=    baseBusiness::Update(m,"");
    return result;
}

bool BsCustomTime::Insert(ModelCustomTime value)
{
    QMap<QString,QVariant> m;
    m.insert(":devicecode",value.devicecode());
    m.insert(":starttime",value.starttime());
    m.insert(":endtime",value.endtime());
    m.insert(":durationofsecond",value.durationofsecond());
    m.insert(":durationofminute",value.durationofminute());
    m.insert(":smsalert",value.smsalert());
    m.insert(":istaskactive",value.isTaskActive());
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

