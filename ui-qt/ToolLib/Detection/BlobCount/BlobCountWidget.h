#ifndef BLOBCOUNTWIDGET_H
#define BLOBCOUNTWIDGET_H

#include <QWidget>
#include <QLibrary>
#include <QDialog>
#include <QLabel>
#include <QTimer>
#include "BlobCountGlobal.h"
namespace Ui {
class BlobCountWidget;
}
typedef QDialog* (*Fun_GetNumkeyBoardDlg)();
typedef QString (*Fun_GetNumString)();
typedef void (*ShowRangeEn)();
typedef QDialog* (*Fun_GetLearnDialog)();
typedef void* (*Fun_SetResultString)(QString str);
class BlobCountWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BlobCountWidget(QWidget *parent = 0);
    ~BlobCountWidget();
    int Set_Parameter_To_Ram();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
    QPoint Get_Image_Pos();
protected:
    bool eventFilter(QObject *watched, QEvent *event);
private slots:
    void on_pushButtonCalc_clicked();
    void CalcTimerSlot();

private:
    Ui::BlobCountWidget *ui;
    QLabel *m_label;
    QLibrary m_keyBoard_Lib;
    QDialog *Numkey;
    BLOBCOUNT_INPUT_PARAM* pInputPara;
    int m_step_index;//当前步骤索引
    QLibrary m_Learn_Lib;
    QTimer *CalcTimer;

    void LoadKeyBoardLib();
    void NumKeyBoardDlg(QObject *watched, QEvent *event, int Min_value, int Max_value);
    void InitData();
    void SetInputData();
    void GetCalcDataShow();
    void LoadLearnLib();
};

#endif // BLOBCOUNTWIDGET_H
