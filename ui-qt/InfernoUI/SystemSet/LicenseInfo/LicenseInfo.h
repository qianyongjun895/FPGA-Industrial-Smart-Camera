#ifndef LICENSEINFO_H
#define LICENSEINFO_H

#include <QWidget>
#include "BusinessData/InterfaceLib/KeyBoardLib.h"
namespace Ui {
class LicenseInfo;
}

class LicenseInfo : public QWidget
{
    Q_OBJECT

public:
    explicit LicenseInfo(QWidget *parent = 0);
    ~LicenseInfo();

signals:
    void LicensePass();

private slots:

    void on_btnRegister_clicked();

    void on_register_code_selectionChanged();

    void on_OK_clicked();

    void on_Cancel_clicked();

private:
    Ui::LicenseInfo *ui;
    KeyBoardLib m_KeyBoardLib;
    void LincenseInfoInit();
};

#endif // LICENSEINFO_H
