#include "modeleventslog.h"


int ModelEventsLog::id() const
{
    return _id;
}

void ModelEventsLog::setId(int id)
{
    _id = id;
}

int ModelEventsLog::devicecode() const
{
    return _devicecode;
}

void ModelEventsLog::setDevicecode(int devicecode)
{
    _devicecode = devicecode;
}

int ModelEventsLog::schedulemode() const
{
    return _schedulemode;
}

void ModelEventsLog::setSchedulemode(int schedulemode)
{
    _schedulemode = schedulemode;
}

QDateTime ModelEventsLog::starttime() const
{
    return _starttime;
}

void ModelEventsLog::setStarttime(const QDateTime &starttime)
{
    _starttime = starttime;
}

QDateTime ModelEventsLog::enddate() const
{
    return _enddate;
}

void ModelEventsLog::setEnddate(const QDateTime &enddate)
{
    _enddate = enddate;
}

int ModelEventsLog::durationofsecond() const
{
    return _durationofsecond;
}

void ModelEventsLog::setDurationofsecond(int durationofsecond)
{
    _durationofsecond = durationofsecond;
}

int ModelEventsLog::durationofminute() const
{
    return _durationofminute;
}

void ModelEventsLog::setDurationofminute(int durationofminute)
{
    _durationofminute = durationofminute;
}

QString ModelEventsLog::mobilenumber() const
{
    return _mobilenumber;
}

void ModelEventsLog::setMobilenumber(const QString &mobilenumber)
{
    _mobilenumber = mobilenumber;
}

int ModelEventsLog::transferstatus() const
{
    return _transferstatus;
}

void ModelEventsLog::setTransferstatus(int transferstatus)
{
    _transferstatus = transferstatus;
}
ModelEventsLog::ModelEventsLog()
{

}

