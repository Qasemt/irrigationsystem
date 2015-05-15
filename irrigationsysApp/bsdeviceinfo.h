#ifndef BSDEVICEINFO_H
#define BSDEVICEINFO_H
#include <modeldeviceinfo.h>

#include <basebusiness.h>
class BsDeviceinfo:baseBusiness
{

public:
    BsDeviceinfo();
    ModelDeviceinfo   fromSqlQuery(QSqlQuery query);

    QList<ModelDeviceinfo> FillData();
    bool Update(ModelDeviceinfo value);
    bool Insert(ModelDeviceinfo value);
    bool RemoveAll ();
    bool Removebycode (int code);

};

#endif // BSDEVICEINFO_H
