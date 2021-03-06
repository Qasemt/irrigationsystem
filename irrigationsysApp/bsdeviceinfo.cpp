#include "bsdeviceinfo.h"

BsDeviceinfo::BsDeviceinfo()
{
    _TableName="deviceinfo";
}

ModelDeviceinfo BsDeviceinfo::fromSqlQuery(QSqlQuery query)
{
    ModelDeviceinfo mdl ;
    mdl.setCode(query.value(query.record().indexOf("code")).toInt());
    mdl.setTitle(query.value(query.record().indexOf("title")).toString());
    mdl.setPowerstatus(query.value(query.record().indexOf("powerstatus")).toBool());
    mdl.setSchedulemode(query.value(query.record().indexOf("schedulemode")).toInt());
    mdl.setDeviceenable(query.value(query.record().indexOf("deviceenable")).toBool());
    mdl.setSmsalertenable(query.value(query.record().indexOf("smsalertenable")).toBool());
    return mdl;
}
ModelDeviceinfo BsDeviceinfo::FillbyCode(int code)
{
    QSqlQuery   query;
    ModelDeviceinfo tmp;
    query=  baseBusiness::FillData("*",QString("code=%1").arg(QString::number(code)));
    while (query.next())
    {
        tmp= fromSqlQuery(query);

    }
    return tmp;
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

QSqlQuery BsDeviceinfo::FillDatasqlmodel()
{
    QSqlQuery query =baseBusiness::FillData();
    qDebug()<<"cnt" <<baseBusiness::numberOfRecords(query)<<endl;
    return query;
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
    bool result= baseBusiness::Update(m,where);
    return result;
}

bool BsDeviceinfo::UpdateDeviceEnableVal(int devicenumber,bool enableval)
{
    QMap<QString,QVariant> m;
    m.insert(":code",devicenumber);
    m.insert(":deviceenable",enableval);
    QString where = QString("code=%1").arg(devicenumber);
    bool result= baseBusiness::Update(m,where);
    return result;
}

bool BsDeviceinfo::UpdateSMSDeviceEnableVal(int devicenumber,bool enableval)
{
    QMap<QString,QVariant> m;
    m.insert(":code",devicenumber);
    m.insert(":smsalertenable",enableval);
    QString where = QString("code=%1").arg(devicenumber);
    bool result= baseBusiness::Update(m,where);
    return result;
}

bool BsDeviceinfo::UpdateScheduleMode(int devicenumber, int shmod, bool issendSMSAlert)
{
    QMap<QString,QVariant> m;
    m.insert(":code",devicenumber);
    m.insert(":schedulemode",shmod);
    m.insert(":smsalertenable",issendSMSAlert);
    QString where = QString("code=%1").arg(devicenumber);
    bool result= baseBusiness::Update(m,where);
    return result;
}


bool BsDeviceinfo::UpdatePowerStatus(int devicenumber,bool pwrStatus)
{
    QMap<QString,QVariant> m;
    m.insert(":powerstatus",pwrStatus);
    QString where = QString("code=%1").arg(devicenumber);
    bool result= baseBusiness::Update(m,where);
    return result;
}

bool BsDeviceinfo::SetPowerOffAllDevice()
{
    QMap<QString,QVariant> m;
    m.insert(":powerstatus",false);
    bool result= baseBusiness::Update(m,"");
    return result;
}
bool BsDeviceinfo::IsPowerOn(int devicenumber)
{
    QString where = QString("code=%1").arg(devicenumber);

    QSqlQuery   query= baseBusiness::FillData("powerstatus",where);
    bool result=false;
    while (query.next())
    {
        result=   query.value(0).toBool();
    }

    return result;
}

//bool BsDeviceinfo::UpdateDeviceEnableVal(int devicenumber,int schmod,int sms)
//{
//    QMap<QString,QVariant> m;
//    m.insert(":code",devicenumber);
//    m.insert(":deviceenable",enableval);
//    QString where = QString("code=%1").arg(devicenumber);
//    bool result= baseBusiness::Update(m,where);
//    return result;
//}
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


