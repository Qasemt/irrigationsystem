#ifndef FRMCMDTEST_H
#define FRMCMDTEST_H

#include <QWidget>

namespace Ui {
class FrmCMDTest;
}

class FrmCMDTest : public QWidget
{
    Q_OBJECT

public:
    explicit FrmCMDTest(QWidget *parent = 0);
    ~FrmCMDTest();

private slots:
    void on_btnChangeSchMode_clicked();

private:
    Ui::FrmCMDTest *ui;
};

#endif // FRMCMDTEST_H
