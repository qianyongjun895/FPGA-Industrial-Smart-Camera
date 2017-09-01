/**
  * @file  [SystemSetWiget.h]
  * @brief  SystemSetWiget
  * @author  <szj>
  * @date  <2017/05/08>
  * @version  <1.0>
  * @note
  * detailed  description
  */
#ifndef SYSTEMSETWIGET_H
#define SYSTEMSETWIGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

namespace Ui {
class SystemSetWiget;
}

class SystemSetWiget : public QWidget
{
    Q_OBJECT

public:
    explicit SystemSetWiget(QWidget *parent = 0);
    ~SystemSetWiget();

    void DeleteWidgetInLayout();

private slots:
    void SetButtonStyle(QPushButton *pre, QPushButton *current);

    void on_btnTsCalibrate_clicked();

    void on_btnVersions_clicked();

    void on_btnLicenseInfo_clicked();

    void on_btnNetWork_clicked();

    void on_btnAdmin_clicked();

    void on_btnUpgrade_clicked();

    void on_btnTaskFile_clicked();

    void on_btnScriptFile_clicked();

    void on_btnToolFile_clicked();

private:
    Ui::SystemSetWiget *ui;

    QPushButton *m_btn_pre;
    QGridLayout *m_ViewLayout;
};

#endif // SYSTEMSETWIGET_H
