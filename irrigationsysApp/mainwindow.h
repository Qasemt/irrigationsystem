#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gsmreader.h>
#include <datahelper.h>
#include <QTimer>
#include <bsdeviceinfo.h>
#include <frmcmdtest.h>
#include <messagewatcher.h>
#include <QDateTime>
#include <bsdeviceinfo.h>
#include <bscustomtime.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_btnOpen_clicked();
    void on_btnClose_clicked();
    void timeoutMaintimer();
    void on_btnfrmCMDtest_clicked();
    void onMessageCMDReceived(QString  cmdMessage);

    void onDailytimeDataReceived(int devicenumber,QDateTime startdatetime,int durationtime,int durationtype,bool issmsalert);
    void onWeeklytimeDataReceived(int devicenumber,int dayindex,QDateTime startdatetime,int durationtime,int durationtype,bool issmsalert);
    void onCustomtimeDataReceived(int devicenumber,QDateTime startdatetime,int durationtime,int durationtype,bool issmsalert);
    void onSchedulemodeDataReceived(int devicenumber,int schmode,bool issmsalertActive);
    void onDeviceEnableDataReceived(int devicenumber,int enablestatus);
private:
    Ui::MainWindow *ui;
    GsmReader *_GsmReader;
    // DataHelper *_DataHelper;
    QTimer *_maintimer;
    void loaddata();

    QSqlQueryModel *_records;
    FrmCMDTest _frmCMDTest;
    BsDeviceinfo _bsDeviceinfo;
    BsCustomTime _bsCustomTime;




};

#endif // MAINWINDOW_H
