#ifndef COMMPARA_H
#define COMMPARA_H

#include <QWidget>
#include <QLibrary>
#include "BusinessData/InterfaceLib/KeyBoardLib.h"
namespace Ui {
class CommPara;
}
typedef QDialog* (*Fun_GetkeyBoardDlg)();
typedef QString (*Fun_GetInputString)();
class CommPara : public QWidget
{
    Q_OBJECT

public:
    explicit CommPara(QWidget *parent = 0);
    ~CommPara();
     QString m_strName;
     QString m_taskNameOrigin;
     int task_index;
     int task_add;
     void InitData();
    void SetTaskName();
protected slots:
    bool eventFilter(QObject *watched, QEvent *event);
private slots:

    void on_BasisButton_clicked();

    void on_AdvancedButton_clicked();

    void on_IOTriggerWayCbB_currentIndexChanged(int index);

    void on_IOTriggerPortCbB_currentIndexChanged(int index);
    void on_groupBoxTrigger_clicked();


    void on_groupBoxCmd_clicked();

    void on_btnModifyTaskName_clicked();

    void on_btnResetTaskName_clicked();

private:
    Ui::CommPara *ui;
    int Model_Flag;///<0:基础; 1:高级
    int OK_IO_Port;
    int NG_IO_Port;
    int m_param_index; // 多点标定参数索引
    int m_scale_param_index; // 刻度校准参数索引
    float m_scale_value; // 刻度校准比例系数
    int Ini_Flag;
    KeyBoardLib m_keyBoard_Lib;
    QDialog *m_dlg;
    void InitIoOutputPara();

    void SetTaskIOTriggerParam();
    void InitIoTriggerParam();
    void InitCalibration();
    void UpdateParamReference(int paramIndex);
    void UpdateScaleParamRef(int paramIndex, float curFloat);
    void ChangeParam();
    void ScaleChangeParam();
    void InitCmdData();
    void KeyBoardDlg(QObject *watched, QEvent *event, int dlg_x, int dlg_y, int String_Len);
    void SetCmdTriggerParam();
    bool isLegal(QString text);
    void SetInfor(QString str,int flag);
    void ComsSelectParam();
    void ShowSelctImageParam(int Param_index);
    void InitComsParam();
};

#endif // COMMPARA_H
