#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <gsmreader.h>

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

private:
    Ui::MainWindow *ui;
    GsmReader *_GsmReader;


};

#endif // MAINWINDOW_H
