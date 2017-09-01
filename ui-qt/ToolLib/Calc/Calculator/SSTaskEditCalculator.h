#ifndef SSTASKEDITCALCULATOR_H
#define SSTASKEDITCALCULATOR_H

#include <QWidget>
#include<QListWidgetItem>
#include "CalcDataSelectDialog.h"
#include <QCloseEvent>
#include <qcombobox.h>
#include "CalcOperatorSelectDialog.h"

namespace Ui {
class SSTaskEditCalculator;
}

class SSTaskEditCalculator : public QWidget
{
    Q_OBJECT

    typedef struct{
        int m_task_index;//数据引用任务索引
        int m_result_index;// 数据引用结果索引

        int m_reg_type;//Modbus寄存器类型
        int m_data_type;// Modbus数据类型
        int m_address;//Modbus 起始地址

        int m_calc_item_index;//计算项索引
        int m_calc_result_index;//计算项结果索引（现在都为1）
        int dataKind; //0手输，1 数据引用 2.modbus,3结果引用
        QString strInputByHand;
    }struSingleData;

    typedef struct{
        struSingleData data1;
        struSingleData data2;
        struSingleData data3;
        struSingleData data4;

        int m_calc_operator; //运算符
        int m_calc_operator_type;//运算符号种类
        int dataCount;//有效数据个数
    }struMutxData;


public:
    explicit SSTaskEditCalculator(QWidget *parent = 0);
    ~SSTaskEditCalculator();
    void Init_Input_Ptr(void *ptr,int i_step_index,int new_flag,void *pen_color);
    int Set_Parameter_To_Ram();

private slots:
    //运算符类型项单击事件
    void on_listWidgetOperatorType_itemClicked(QListWidgetItem *item);
    //删除
    void on_btnDel_clicked();
    //增加
    void on_btnAdd_clicked();
    //修改确定
    void on_btnEdit_clicked();
    //运算符列表项单击事件
    void on_listWidgetOperator_itemClicked(QListWidgetItem *item);

    //清空
    void on_btnClear_clicked();

    //表格列表单击事件
    void on_tableWidgetData_clicked(const QModelIndex &index);

    void on_tableWidgetData_cellDoubleClicked(int row, int column);

    void on_btnDataOne_clicked();

    void on_btnDataTwo_clicked();

    void on_btnDataThree_clicked();

    void on_btnDataFour_clicked();

private:
    Ui::SSTaskEditCalculator *ui;
    //CalcuatorData *p_CalcuatorData;
    bool m_b_flag;
    QString m_str_operator_type;
    QStringList m_Modbus_reg_list;
    QStringList m_Modbus_type_list;
    QStringList m_pLc_type_list;
    QString m_Data_Input;
    QVector<struMutxData> m_data_vt;
    int m_listTypeRow;
    int m_listOperatorRow;
    int m_calc_operator;
    int m_calc_operator_type;
    int m_use_data_count;
    //当前任务步骤号
    int m_currentStep;
    QStringList str_operator;
    QStringList str_operator_info;

    struSingleData m_data[4];
    QString strInfo;
    CalcOperatorSelectDialog *m_CalcOperatorSelectDialog;

    //初始表格列
    void IniTabaleHead();
    //设置数据控件使能
    void SetInputDataControlEnable(bool bflag1,bool bflag2,bool bflag3,bool bflag4);
    //向表格中增加数据
    void AddDataToTable(QString strOperatorType,QString strData1,QString strData2,QString strData3,QString strData4);
    //修改表格中数据
    void EditDataToTable(QString strOperatorType,QString strData1,QString strData2,QString strData3,QString strData4);
    //根据运算符确定运算符类型
    void FindOperator(QString strType);
    //根据运算符枚举类型转换为运算符的字符串
    QString GetOperator(int calc_operator);
    //模仿单击运算符类型，单南运符列表
    void EditIniList();
    //设置下拉框最先显示的字符串
    void SetComboBoxIndex(QString strData,QComboBox *pcontrol,int index);
    //下发数据到monkeyLib
    void SendDataToMonkeyLib();
    //判断重复数据
    bool DataIsInTable(QString strOperatorType,QString strData1,QString strData2,QString strData3,QString strData4);
    //删除某一行表格后，判断后面数据的结果引用是否有效
    void DeletTableAndEditData(int index);

    //判断表格有没有错误数据
    bool IsTableErrorData();

    //解析表格数据后并设置到monkeyLib中
    void AnalysisAndSetDataToLib(QString strData, int iTableIndex, int DataIndex);


    //判断数据是不是float
    bool IsDataFloat(QString strData);

    //根据具体的运算符设置相关的信息
    void SetDataByOperator(int Op_type_index, int Op_index);

    void setBtnEnable(bool bflag1,bool bflag2,bool bflag3,bool bflag4);

    void setCellClear(int paramCount);
};

#endif // SSTASKEDITCALCULATOR_H
