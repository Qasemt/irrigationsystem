#ifndef BSSYSTEMPARAMETER_H
#define BSSYSTEMPARAMETER_H
#include <qstring.h>
#include <modelsystemparameter.h>

#include <QSqlQuery>
#include <qvariant.h>
#include <QList>
#include <datahelper.h>


class Bssystemparameter
{
public:
    enum eParamKeys
    {
        pk_apn=1,
        pk_serverip=2,
        pk_serverport=3,
        pk_gprsportname=4,
        pk_gpsportname=5,
        pk_busnumber=6,
        pk_driverpersonnelnumber=7,
        pk_vtlcode=8,
        pk_mainlinecode=9,
        pk_CardReaderPortName=10,
        pk_gispath=11
    };
    Bssystemparameter();

    ModelSystemParameter  GetValueParam(eParamKeys key);
    ModelSystemParameter   fromSqlQuery(QSqlQuery query);


    QList<ModelSystemParameter> FillData();
    bool UpdateParam(int key,QString title,QString value);
    bool InsertParam(int key,QString title,QString value);

};

#endif // BSSYSTEMPARAMETER_H
