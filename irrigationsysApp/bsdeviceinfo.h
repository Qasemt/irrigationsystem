#ifndef BSDEVICEINFO_H
#define BSDEVICEINFO_H
#include <modeldeviceinfo.h>
#include <QSqlQueryModel>
#include <basebusiness.h>
class BsDeviceinfo:baseBusiness
{

public:
    BsDeviceinfo();
    ModelDeviceinfo   fromSqlQuery(QSqlQuery query);

    QList<ModelDeviceinfo> FillData();
    QSqlQuery FillDatasqlmodel();
    bool Update(ModelDeviceinfo value);
    bool Insert(ModelDeviceinfo value);
    bool RemoveAll ();
    bool Removebycode (int code);

    bool UpdateDeviceEnableVal(int devicenumber, bool enableval);
};

#endif // BSDEVICEINFO_H
