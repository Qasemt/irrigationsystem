#ifndef DEVICEPROCESS_H
#define DEVICEPROCESS_H
#include <QTimer>
#include <QObject>
#include <qdebug.h>
class DeviceProcess : public QObject
{
    Q_OBJECT
private:
    QTimer *_maintimer;

public:
    explicit DeviceProcess(QObject *parent = 0);
void deviceCheck(int deviceCode);

void LoadData();
void ProcCustomtime();
void ProcDilytime();
void ProcWeeklytime();
signals:

public slots:
 void timeoutMaintimer();


};

#endif // DEVICEPROCESS_H
