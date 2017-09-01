#ifndef MITFXPLCWIDGET_H
#define MITFXPLCWIDGET_H

#include <QWidget>
#include <QLibrary>
#include "MitFxPlcListWidgetItem.h"
namespace Ui {
class MitFxPlcWidget;
}
typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();
class MitFxPlcWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MitFxPlcWidget(QWidget *parent = 0);
    ~MitFxPlcWidget();

    void SetMitFxPLCConfig();
private slots:
    void on_pushButton_Add_clicked();

    void on_pushButton_Del_clicked();

    void on_pushButton_Up_clicked();

    void on_pushButton_Down_clicked();

protected slots:
    bool eventFilter(QObject *watched, QEvent *event);
private:
    Ui::MitFxPlcWidget *ui;
    QLibrary m_keyBoard_Lib;
    QDialog *Numkey;
    void AddListWisgetItem(MitFxPlcListWidgetItem *item);
    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value);
    void AddRDMRegItem();
    void AddWRMRegItem();
    void AddRDDRegItem();
    void AddWRDRegItem();
};

#endif // MITFXPLCWIDGET_H
