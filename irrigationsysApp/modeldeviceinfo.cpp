#include "modeldeviceinfo.h"


int ModelDeviceinfo::code() const
{
    return _code;
}

void ModelDeviceinfo::setCode(int code)
{
    _code = code;
}

QString ModelDeviceinfo::title() const
{
    return _title;
}

void ModelDeviceinfo::setTitle(const QString &title)
{
    _title = title;
}

bool ModelDeviceinfo::powerstatus() const
{
    return _powerstatus;
}

void ModelDeviceinfo::setPowerstatus(bool powerstatus)
{
    _powerstatus = powerstatus;
}

int ModelDeviceinfo::schedulemode() const
{
    return _schedulemode;
}

void ModelDeviceinfo::setSchedulemode(int schedulemode)
{
    _schedulemode = schedulemode;
}

bool ModelDeviceinfo::deviceenable() const
{
    return _deviceenable;
}

void ModelDeviceinfo::setDeviceenable(bool deviceenable)
{
    _deviceenable = deviceenable;
}
ModelDeviceinfo::ModelDeviceinfo()
{

}

