#ifndef OSDCOLORSETDLG_H
#define OSDCOLORSETDLG_H

#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include "BusinessData/InterfaceLib/KeyBoardLib.h"
#include "TaskGlobal.h"
namespace Ui {
class OSDColorSetDlg;
}

class OSDColorSetDlg : public QDialog
{
    Q_OBJECT

public:
    explicit OSDColorSetDlg(QWidget *parent = 0);
    ~OSDColorSetDlg();
    void SetStep(int step);
    void SetLabel(QLabel *lable);
    void GetDataFromLib();
    void SetData();
    void InitLibColor();
    void *GetPenColorDrr();
    void SetWidget(QWidget *widget);
private slots:
    void on_btnOk_clicked();

    void on_btnQuit_clicked();

    void on_comboBoxImgBorderColor_currentIndexChanged(int index);

    void on_comboBoxParaEditColor_currentIndexChanged(int index);

    void on_comboBoxParaSelectColor_currentIndexChanged(int index);

    void on_comboBoxParaCalColor_currentIndexChanged(int index);

    void on_comboBoxEdgePointColor_currentIndexChanged(int index);

    void on_comboBoxAreaSelectColor_currentIndexChanged(int index);

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::OSDColorSetDlg *ui;
    void initCombColor(QComboBox *cmb);
    int m_step;
    int iFirst;
    KeyBoardLib m_keyBoardLib;
    QLabel *m_label;
    QWidget *m_widget;
    int OSDAreaSelectColor;
    int OSDEdgePointColor;
    int OSDImageBorderColor;
    int OSDCalcColor;
    int OSDParamEditColor;
    int OSDCheckedColor;

    int OSDAreaSelectWidth;
    int OSDEdgePointWidth;
    int OSDImageBorderWidth;
    int OSDCalcWidth;
    int OSDParamEditWidth;
    int OSDCheckedWidth;

    void InstallEvent();
    void UninstallEvent();
    void SelectWidth(QLineEdit *txtLineEdit);

    void GetColor(int index);
    void InitControl();
    void RefreshWidget();
    int GetWidthValueFromLib(unsigned char value);

};

#endif // OSDCOLORSETDLG_H
