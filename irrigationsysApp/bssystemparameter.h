#ifndef BSSYSTEMPARAMETER_H
#define BSSYSTEMPARAMETER_H
#include <qstring.h>
#include <modelsystemparameter.h>

#include <QSqlQuery>
#include <qvariant.h>
#include <QList>
#include <datahelper.h>
#include <QSqlRecord>
#include <QDebug>


class Bssystemparameter
{
public:
    enum eParamKeys
    {
        pk_apn=1,
        pk_serverip=2,
        pk_serverport=3,


    };
    Bssystemparameter();

    ModelSystemParameter  GetValueParam(eParamKeys key);
    ModelSystemParameter   fromSqlQuery(QSqlQuery query);


    QList<ModelSystemParameter> FillData();
    bool Update(int key,QString title,QString value);
    bool Insert(int key,QString title,QString value);

};

#endif // BSSYSTEMPARAMETER_H
