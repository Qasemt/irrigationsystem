#include "modelmanualtime.h"


int ModelManualTime::id() const
{
    return _id;
}

void ModelManualTime::setId(int id)
{
    _id = id;
}

int ModelManualTime::devicecode() const
{
    return _devicecode;
}

void ModelManualTime::setDevicecode(int devicecode)
{
    _devicecode = devicecode;
}

QDateTime ModelManualTime::starttime() const
{
    return _starttime;
}

void ModelManualTime::setStarttime(const QDateTime &starttime)
{
    _starttime = starttime;
}

QDateTime ModelManualTime::enddate() const
{
    return _enddate;
}

void ModelManualTime::setEnddate(const QDateTime &enddate)
{
    _enddate = enddate;
}

int ModelManualTime::durationofsecond() const
{
    return _durationofsecond;
}

void ModelManualTime::setDurationofsecond(int durationofsecond)
{
    _durationofsecond = durationofsecond;
}

int ModelManualTime::durationofminute() const
{
    return _durationofminute;
}

void ModelManualTime::setDurationofminute(int durationofminute)
{
    _durationofminute = durationofminute;
}

bool ModelManualTime::smsalert() const
{
    return _smsalert;
}

void ModelManualTime::setSmsalert(bool smsalert)
{
    _smsalert = smsalert;
}
ModelManualTime::ModelManualTime()
{

}

