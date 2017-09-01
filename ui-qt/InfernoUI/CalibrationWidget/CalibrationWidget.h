#ifndef CALIBRATIONWIDGET_H
#define CALIBRATIONWIDGET_H

#include <QWidget>
#include <stdbool.h>
#include <QGridLayout>
#include <QTime>
#include <QTimer>
#include "BusinessData/InterfaceLib/KeyBoardLib.h"
#include <QHash>
namespace Ui {
class CalibrationWidget;
}

class CalibrationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CalibrationWidget(QWidget *parent = 0);
    ~CalibrationWidget();
    void SetRobotID(int id);
    int GetRobotID();

private slots:

    void on_btnNew_clicked();

    void on_btnEdit_clicked();

    void on_btnDelete_clicked();

    void on_listWidgetParamType_currentRowChanged(int currentRow);

    void on_tabWidget_tabBarClicked(int index);

    void on_btnRename_clicked();

    void RecieveRenameText(QString text);

    void on_btnXSub_pressed();

    void on_btnXSub_released();

    void on_btnYSub_pressed();

    void on_btnYSub_released();

    void on_btnZSub_pressed();

    void on_btnZSub_released();

    void on_btnASub_pressed();

    void on_btnASub_released();

    void on_btnBSub_pressed();

    void on_btnBSub_released();

    void on_btnCSub_pressed();

    void on_btnCSub_released();
    void on_btnXAdd_pressed();

    void on_btnXAdd_released();

    void on_btnYAdd_pressed();

    void on_btnYAdd_released();

    void on_btnZAdd_pressed();

    void on_btnZAdd_released();

    void on_btnAAdd_pressed();

    void on_btnAAdd_released();

    void on_btnBAdd_pressed();

    void on_btnBAdd_released();

    void on_btnCAdd_pressed();

    void on_btnCAdd_released();

    void on_btnElectrify_clicked();

    void on_btnBlackOut_clicked();

    void on_bntGrpPowerOn_clicked();

    void on_bntGrpPowerOff_clicked();

    void on_btnReset_clicked();

    void on_btnStop_clicked();

    void on_btnJ1Sub_pressed();

    void on_btnJ1Sub_released();
    void on_btnJ2Sub_pressed();
    void on_btnJ2Sub_released();
    void on_btnJ3Sub_pressed();
    void on_btnJ3Sub_released();
    void on_btnJ4Sub_pressed();
    void on_btnJ4Sub_released();
    void on_btnJ5Sub_pressed();
    void on_btnJ5Sub_released();
    void on_btnJ6Sub_pressed();
    void on_btnJ6Sub_released();


    void on_btnJ1Add_pressed();
    void on_btnJ1Add_released();
    void on_btnJ2Add_pressed();
    void on_btnJ2Add_released();
    void on_btnJ3Add_pressed();
    void on_btnJ3Add_released();
    void on_btnJ4Add_pressed();
    void on_btnJ4Add_released();
    void on_btnJ5Add_pressed();
    void on_btnJ5Add_released();
    void on_btnJ6Add_pressed();
    void on_btnJ6Add_released();
    void TimeOutFun();



    void on_StartpushButton_clicked();

    void on_btnNext_clicked();

    void on_btnPre_clicked();

    void on_pushButton_Manual_send_clicked();

    void ShowRecvData();
protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::CalibrationWidget *ui;
    QWidget *rowInput;
    int m_AxisID;
    int m_Derection;
    QTime m_start;
    QTime m_end;
    QTimer *m_timer;
    QHash<int,int> User_List_index;
    QTimer *Recv_time;
    int Recv_count;
    int m_kind;
    KeyBoardLib m_keyBoardLib;
    int m_robot_id; // 机器人ID

    void MultipointDemarcateParamListInit();
    void ScaleCalibrationParamListInit();
    void ParamReferencePanelInit();
    void ParamReferencePanelUpdate();
    int IsTimeOut();
    void OnShortJogL();
    void OnLongJogL();
    void OnShortJogJ(); //角度
    void OnLongJogJ();
    void OnMoveRelL();
    void OnMoveRelJ();
    void OnReadAcsActualPos();
    void OnReadPcsActualPos();
    void InitEthernet();
    int SetEthernetParam();
    void SetGroupBoxEnable(int blag);
    void IniUserDefList();
};

#endif // CALIBRATIONWIDGET_H
