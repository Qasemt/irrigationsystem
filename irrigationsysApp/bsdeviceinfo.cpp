#include "bsdeviceinfo.h"

BsDeviceinfo::BsDeviceinfo()
{

}

ModelDeviceinfo BsDeviceinfo::fromSqlQuery(QSqlQuery query)
{
    ModelDeviceinfo mdl ;
    mdl.setCode(query.value(query.record().indexOf("code")).toInt());
    mdl.setTitle(query.value(query.record().indexOf("title")).toString());
    mdl.setPowerstatus(query.value(query.record().indexOf("powerstatus")).toBool());
    mdl.setSchedulemode(query.value(query.record().indexOf("schedulemode")).toInt());
    mdl.setDeviceenable(query.value(query.record().indexOf("deviceenable")).toBool());
    return mdl;
}

QList<ModelDeviceinfo> BsDeviceinfo::FillData()
{
    QSqlQuery   query;
    QList<ModelDeviceinfo> tmplist;
    query=  baseBusiness::FillData();
    while (query.next())
    {
        ModelDeviceinfo md= fromSqlQuery(query);
        tmplist.append(md);
    }
    return tmplist;
}

bool BsDeviceinfo::Update(ModelDeviceinfo value)
{
    QMap<QString,QVariant> m;
    m.insert(":code",value.code());
    m.insert(":title",value.title());
    m.insert(":powerstatus",value.powerstatus());
    m.insert(":schedulemode",value.schedulemode());
    m.insert(":deviceenable",value.deviceenable());
    QString where = QString("code=%1").arg(value.code());
    bool result=      baseBusiness::Update(m,where);
    return result;
}

bool BsDeviceinfo::Insert(ModelDeviceinfo value)
{
    QMap<QString,QVariant> m;
    m.insert(":code",value.code());
    m.insert(":title",value.title());
    m.insert(":powerstatus",value.powerstatus());
    m.insert(":schedulemode",value.schedulemode());
    m.insert(":deviceenable",value.deviceenable());
    bool result= baseBusiness::Insert(m);
    return result;
}

bool BsDeviceinfo::RemoveAll()
{
  return  baseBusiness::RemoveAll();
}

bool BsDeviceinfo::Removebycode(int code)
{
    return  baseBusiness::Removebywhere(QString("code = %1").arg(code));
}


