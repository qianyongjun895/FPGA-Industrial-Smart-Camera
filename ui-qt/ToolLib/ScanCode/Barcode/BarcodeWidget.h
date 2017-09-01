#ifndef BARCODEWIDGET_H
#define BARCODEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLibrary>
#include "BarcodeGlobal.h"
#include <QLineEdit>
#include <QCheckBox>
#include <QHash>
namespace Ui {
class BarcodeWidget;
}
typedef QDialog* (*Fun_GetkeyBoardDlg)();
typedef QString (*Fun_GetInputString)();

typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();
typedef void (*ShowRangeEn)();
class BarcodeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BarcodeWidget(QWidget *parent = 0);
    ~BarcodeWidget();
    void Init_Input_Ptr(void *pInpuPara,int i_step_index ,int new_flag,void *pen_color);
    int Set_Parameter_To_Ram();
    QPoint Get_Image_Pos();
protected:
    bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void on_lineEdit_Data_Start_Bit_textChanged(const QString &arg1);

    void on_lineEdit_Data_Length_textChanged(const QString &arg1);

    void on_checkBox_Data1_clicked();
    void on_checkBox_Data2_clicked();
    void on_checkBox_Data3_clicked();
    void on_checkBox_Data4_clicked();

    void on_checkBox_Output_Length_clicked();

private:
    Ui::BarcodeWidget *ui;
    BARCODE_INPUT_PARAM* pInputPara;
    int m_step_index;//当前步骤索引
    QLabel *m_label;
    QLibrary m_keyBoard_Lib;
    QDialog *m_dlg;
    QDialog *Numkey;

    QHash<QCheckBox*, int>Data_Flag;
    QHash<QLineEdit*, int>Data_start_bit;
    QHash<QLineEdit*, int>Data_length;

    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, int clear_en, int Min_value, int Max_value);
    void KeyBoardDlg(QObject *watched, QEvent *event, int dlg_x, int dlg_y, int String_Len);
    void DataEnable();
    void IniData();
    int CheckSetParam();
};

#endif // BARCODEWIDGET_H
