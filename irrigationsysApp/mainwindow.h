#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gsmreader.h>
#include <datahelper.h>
#include <QTimer>
#include <bsdeviceinfo.h>
#include <frmcmdtest.h>
#include <messagewatcher.h>
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
private:
    Ui::MainWindow *ui;
    GsmReader *_GsmReader;
    // DataHelper *_DataHelper;
    QTimer *_maintimer;
    void loaddata();
    BsDeviceinfo _bsDeviceinfo;
    QSqlQueryModel *_records;
    FrmCMDTest _frmCMDTest;



};

#endif // MAINWINDOW_H
