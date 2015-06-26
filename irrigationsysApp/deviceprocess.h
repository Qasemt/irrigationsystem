#ifndef DEVICEPROCESS_H
#define DEVICEPROCESS_H
#include <QTimer>
#include <QObject>
#include <qdebug.h>
#include <modelcustomtime.h>
#include <modeldeviceinfo.h>
#include <bsdeviceinfo.h>
#include <aenums.h>
#include <bscustomtime.h>
#include <QDateTime>
#include <QList>
#include <messagewatcher.h>
#include <bsmodeldailytime.h>
#include <bsweeklytime.h>
class DeviceProcess : public QObject
{
    Q_OBJECT
private:
    QTimer *_maintimer;
    ModelDeviceinfo  _ModelDeviceinfo;

    QList<ModelCustomTime> _ModelCustomTimes;
    QList<ModelDailyTime> _ModelDailyTimes;
    QList<ModelWeeklyTime> _ModelWeeklyTimes;

    BsDeviceinfo _bsDeviceinfo;
    BsCustomTime _BsCustomTime;
    BsModelDailyTime _BsModelDailyTime;
    BsWeeklytime _BsWeeklytime;
    int _Devicecode;

    bool istimebetweenTimeofday(QDateTime time, QDateTime startTime, QDateTime endTime);
public:
    explicit DeviceProcess(QObject *parent = 0);
void deviceCheck(int deviceCode);

void LoadData();
void ProcCustomtime();
void ProcDilytime();
void ProcWeeklytime();
bool isTimeBetween(QDateTime time, QDateTime startTime, QDateTime endTime);


signals:


public slots:
void timeoutMaintimer();
void onRefreshData();


};

#endif // DEVICEPROCESS_H
