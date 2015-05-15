#include "modelcustomtime.h"


int ModelCustomTime::id() const
{
    return _id;
}

void ModelCustomTime::setId(int id)
{
    _id = id;
}

int ModelCustomTime::devicecode() const
{
    return _devicecode;
}

void ModelCustomTime::setDevicecode(int devicecode)
{
    _devicecode = devicecode;
}

int ModelCustomTime::dayindex() const
{
    return _dayindex;
}

void ModelCustomTime::setDayindex(int dayindex)
{
    _dayindex = dayindex;
}

QDateTime ModelCustomTime::starttime() const
{
    return _starttime;
}

void ModelCustomTime::setStarttime(const QDateTime &starttime)
{
    _starttime = starttime;
}

QDateTime ModelCustomTime::enddate() const
{
    return _enddate;
}

void ModelCustomTime::setEnddate(const QDateTime &enddate)
{
    _enddate = enddate;
}

int ModelCustomTime::durationofsecond() const
{
    return _durationofsecond;
}

void ModelCustomTime::setDurationofsecond(int durationofsecond)
{
    _durationofsecond = durationofsecond;
}

int ModelCustomTime::durationofminute() const
{
    return _durationofminute;
}

void ModelCustomTime::setDurationofminute(int durationofminute)
{
    _durationofminute = durationofminute;
}

bool ModelCustomTime::smsalert() const
{
    return _smsalert;
}

void ModelCustomTime::setSmsalert(bool smsalert)
{
    _smsalert = smsalert;
}
ModelCustomTime::ModelCustomTime()
{
    
}

