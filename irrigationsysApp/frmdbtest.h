#ifndef FRMDBTEST_H
#define FRMDBTEST_H

#include <QWidget>
#include <bssystemparameter.h>

namespace Ui {
class FrmDBTest;
}

class FrmDBTest : public QWidget
{
    Q_OBJECT

public:
    explicit FrmDBTest(QWidget *parent = 0);
    ~FrmDBTest();

private slots:
    void on_btnGetParams_clicked();


private:
    Ui::FrmDBTest *ui;
    Bssystemparameter _bsParams;
};

#endif // FRMDBTEST_H
