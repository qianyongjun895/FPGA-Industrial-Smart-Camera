#ifndef CALCUATORDATA_H
#define CALCUATORDATA_H

#include <QTimer>
#include "CalculatorGlobal.h"
class CalcuatorData
{
public:
    CalcuatorData();
    ~CalcuatorData();

    typedef enum {
        CALC_OPERATOR_ADD = 0,
        CALC_OPERATOR_SUBTRACT,
        CALC_OPERATOR_MULTIPLY,
        CALC_OPERATOR_DIVIDE,
        CALC_OPERATOR_MOD,
        CALC_OPERATOR_POWER,
        CALC_OPERATOR_LOGIC_NOT,
        CALC_OPERATOR_LOGIC_AND,
        CALC_OPERATOR_LOGIC_OR,
        CALC_OPERATOR_LOGIC_XOR,
        CALC_OPERATOR_COMPARE_EQUAL,
        CALC_OPERATOR_COMPARE_UNEQUAL,
        CALC_OPERATOR_COMPARE_GREATER,
        CALC_OPERATOR_COMPARE_SMALLER,
        CALC_OPERATOR_COMPARE_GREATER_OR_EQUAL,
        CALC_OPERATOR_COMPARE_SMALLER_OR_EQUAL,
        CALC_OPERATOR_MAX,
        CALC_OPERATOR_MIN,
        CALC_OPERATOR_MAX_INDEX,
        CALC_OPERATOR_MIN_INDEX,
        CALC_OPERATOR_ABS,
        CALC_OPERATOR_DEG,
        CALC_OPERATOR_RAD,
        CALC_OPERATOR_SQR,
        CALC_OPERATOR_SQRT,
        CALC_OPERATOR_CEIL,
        CALC_OPERATOR_FLOOR,
        CALC_OPERATOR_INT,
        CALC_OPERATOR_ROUND,
        CALC_OPERATOR_LN,
        CALC_OPERATOR_LG,
        CALC_OPERATOR_COS,
        CALC_OPERATOR_SIN,
        CALC_OPERATOR_TAN,
        CALC_OPERATOR_ACOS,
        CALC_OPERATOR_ASIN,
        CALC_OPERATOR_ATAN,
        CALC_OPERATOR_ATAN_P1P2,
        CALC_OPERATOR_BIT_NOT,
        CALC_OPERATOR_BIT_AND,
        CALC_OPERATOR_BIT_OR,
        CALC_OPERATOR_BIT_XOR,
        CALC_OPERATOR_END
    }CALC_OPERATOR;

    typedef enum {
        CALCOP_TYPE_ARITHMETIC_OPERATOR = 0,
        CALCOP_TYPE_LOGICAL_OPERATOR,
        CALCOP_TYPE_COMPARE_OPERATOR,
        CALCOP_TYPE_GENERAL_FUNCTION,
        CALCOP_TYPE_TRIGONOMETRY_FUNCTION,
        CALCOP_TYPE_BIT_OPERATOR,
        CALCOP_TYPE_END
    } CALC_OPERATOR_TYPE;

    typedef enum {
        MODBUS_DATA_TYPE_INT = 0,
        MODBUS_DATA_TYPE_FLOAT,
        MODBUS_DATA_TYPE_LONG,
        MODBUS_DATA_TYPE_DOUBLE,
        MODBUS_DATA_TYPE_INT_R,
        MODBUS_DATA_TYPE_FLOAT_R,
        MODBUS_DATA_TYPE_LONG_R,
        MODBUS_DATA_TYPE_DOUBLE_R,
        MODBUS_DATA_TYPE_END
    } MODBUS_DATA_TYPE;



    int LoadPositionData(void* pInpuPara, int TaskListIndex, int new_flag);

    //设置完成 返回-1：失败 0：成功
    int LearnStart(int TaskListIndex);

    //获取列表任务数
    unsigned int GetListAllTask();

    //获取任务字符串(index:任务index)
    QString GetTaskListString(unsigned int index);

    //获取任务多结果字符串(index:任务index)
    QStringList GetTaskResultString(unsigned int index);

    //获取任务类型对应的发送数据显示字符串(index:任务index)
    QStringList GetSendDataStringList(unsigned int index, unsigned int result_index);

    //获取结果索引时的转换函数，返回值为界面显示需要的index(从1开始)
    //count:返回界面显示的索引,对应GetTaskResultString函数(从0开始)，如果等于-1：不是多结果任务，
    //task_index:任务索引，result_index：Result_ID索引
    int NewGetResultID(int* count, int task_index, unsigned int result_index);

    //设置结果索引时的转换函数，返回值为SSP需要的result_ID
    //(task_index:任务索引，rst_index:第几个结果的索引（从0开始）; result_ID:任务结果数据索引（从0开始） )
    unsigned int NewSetResultID(int task_index, int rst_index, unsigned int result_ID);


    //设置之前清空计算数据
    void CleanData();


    //获取计算项的总数
    unsigned int GetCalcCount(){return calc_item_count;}

    //获取计算项选中标志
    unsigned char GetSelectFlag(unsigned int calc_index){return calc_select_flag[calc_index];}

    //获取计算的运算符种类(运算符种类在枚举CALC_OPERATOR_TYPE中)
    unsigned short GetMainType(unsigned int calc_index){return calc_item[calc_index].calc_main_type;}

    //获取对应的操作符(操作符在枚举CALC_OPERATOR中)
    unsigned short GetSubType(unsigned int calc_index){return calc_item[calc_index].calc_sub_type;}

    //获取操作目数
    unsigned int GetOprandNum(unsigned int calc_index){return calc_item[calc_index].oprand_num;}

    //获取计算数据的数据来源类型
    /*#define CALC_DATA_MANUAL	1
      #define CALC_DATA_REF		2
      #define CALC_DATA_MODBUS	3
      #define CALC_DATA_PRE_ITEM 4
      #define CALC_DATA_MIT_FX_PLC	    5*/
    unsigned int GetParamType(unsigned int calc_index, unsigned int param_index){return calc_item[calc_index].calc_op[param_index].op_type;}

    //获取手动输入的数据
    float GetManualInputValue(unsigned int calc_index, unsigned int param_index){return calc_item[calc_index].calc_op[param_index].oprand.manual_op.manual_input_op;}

    //获取关联任务的任务索引
    unsigned short GetLinkDataStepIndex(unsigned int calc_index, unsigned int param_index){return calc_item[calc_index].calc_op[param_index].oprand.ref_value_op.step_index;}

    //获取关联任务的结果索引
    unsigned short GetLinkDataResultIndex(unsigned int calc_index, unsigned int param_index){return calc_item[calc_index].calc_op[param_index].oprand.ref_value_op.result_index;}

    //获取引用modbus的寄存器类型(保持寄存器：MODBUS_REG_TYPE_HOLD:0; 输入寄存器：MODBUS_REG_TYPE_INPUT:1)
    unsigned char GetModbusRegType(unsigned int calc_index, unsigned int param_index){return calc_item[calc_index].calc_op[param_index].oprand.modbus_op.reg_type;}

    //获取引用modbus寄存器的数据类型(数据类型在枚举CALC_MODBUS_DATA_TYPE中)
    unsigned char GetModbusDataType(unsigned int calc_index, unsigned int param_index){return calc_item[calc_index].calc_op[param_index].oprand.modbus_op.data_type;}

    //获取引用modbus寄存器的地址
    unsigned short GetModbusRegAddr(unsigned int calc_index, unsigned int param_index){return calc_item[calc_index].calc_op[param_index].oprand.modbus_op.reg_addr;}

    //获取引用PLC寄存器的数据类型(数据类型在枚举CALC_MODBUS_DATA_TYPE中)
    unsigned char GetPLCDataType(unsigned int calc_index, unsigned int param_index){return calc_item[calc_index].calc_op[param_index].oprand.mit_fx_plc_op.data_type;}

    //获取引用PLC寄存器的地址
    unsigned short GetPLCRegAddr(unsigned int calc_index, unsigned int param_index){return calc_item[calc_index].calc_op[param_index].oprand.mit_fx_plc_op.reg_addr;}


    //获取引用计算项的索引
    unsigned short GetItemIndex(unsigned int calc_index, unsigned int param_index){return calc_item[calc_index].calc_op[param_index].oprand.pre_item.pre_item_id;}

    //获取引用计算项的结果索引
    unsigned short GetItemResultIndex(unsigned int calc_index, unsigned int param_index){return calc_item[calc_index].calc_op[param_index].oprand.pre_item.result_id;}

    //获取数据输入类型
    unsigned int GetDataInputType(unsigned int calc_index, unsigned int param_index){return calc_item[calc_index].calc_op[param_index].oprand.data_input.data_input_type;}

    //获取数据输入的地址
    unsigned int GetDataInputAddr(unsigned int calc_index, unsigned int param_index){return calc_item[calc_index].calc_op[param_index].oprand.data_input.data_input_addr;}





    //设置计算项的总数
    void SetCalcCount(unsigned int count){calc_item_count = count;}

    //设置计算项选中标志
    void SetSelectFlag(unsigned int calc_index, unsigned char flag){calc_select_flag[calc_index] = flag;}

    //设置计算的运算符种类(运算符种类在枚举CALC_OPERATOR_TYPE中)
    void SetMainType(unsigned int calc_index, unsigned short main_type){calc_item[calc_index].calc_main_type = main_type;}

    //设置对应的操作符(操作符在枚举CALC_OPERATOR中)
    void SetSubType(unsigned int calc_index, unsigned short sub_type){calc_item[calc_index].calc_sub_type = sub_type;}

    //设置操作目数
    void SetOprandNum(unsigned int calc_index, unsigned int num){calc_item[calc_index].oprand_num = num;}

    //设置计算数据的数据来源类型
    /*#define CALC_DATA_MANUAL	1
      #define CALC_DATA_REF		2
      #define CALC_DATA_MODBUS	3
      #define CALC_DATA_PRE_ITEM 4
      #define CALC_DATA_MIT_FX_PLC	    5  */
    void SetParamType(unsigned int calc_index, unsigned int param_index, unsigned int data_source){calc_item[calc_index].calc_op[param_index].op_type = data_source;}

    //设置手动输入的数据
    void SetManualInputValue(unsigned int calc_index, unsigned int param_index, float m_data){calc_item[calc_index].calc_op[param_index].oprand.manual_op.manual_input_op = m_data;}

    //设置关联任务的任务索引
    void SetLinkDataStepIndex(unsigned int calc_index, unsigned int param_index, unsigned short task_index){calc_item[calc_index].calc_op[param_index].oprand.ref_value_op.step_index = task_index;}

    //设置关联任务的结果索引
    void SetLinkDataResultIndex(unsigned int calc_index, unsigned int param_index, unsigned short result_index){calc_item[calc_index].calc_op[param_index].oprand.ref_value_op.result_index = result_index;}

    //设置引用modbus的寄存器类型(保持寄存器：MODBUS_REG_TYPE_HOLD:0; 输入寄存器：MODBUS_REG_TYPE_INPUT:1)
    void SetModbusRegType(unsigned int calc_index, unsigned int param_index, unsigned char reg_type){calc_item[calc_index].calc_op[param_index].oprand.modbus_op.reg_type = reg_type;}

    //设置引用modbus寄存器的数据类型(数据类型在枚举CALC_MODBUS_DATA_TYPE中)
    void SetModbusDataType(unsigned int calc_index, unsigned int param_index, unsigned char data_type){calc_item[calc_index].calc_op[param_index].oprand.modbus_op.data_type = data_type;}

    //设置引用modbus寄存器的地址
    void SetModbusRegAddr(unsigned int calc_index, unsigned int param_index, unsigned short reg_addr){calc_item[calc_index].calc_op[param_index].oprand.modbus_op.reg_addr = reg_addr;}

    //设置引用PLC寄存器的数据类型(数据类型在枚举CALC_MODBUS_DATA_TYPE中)
    void SetPLCDataType(unsigned int calc_index, unsigned int param_index, unsigned char data_type){calc_item[calc_index].calc_op[param_index].oprand.mit_fx_plc_op.data_type = data_type;}

    //设置引用PLC寄存器的地址
    void SetPLCRegAddr(unsigned int calc_index, unsigned int param_index, unsigned short reg_addr){calc_item[calc_index].calc_op[param_index].oprand.mit_fx_plc_op.reg_addr = reg_addr;}


    //设置引用计算项的索引
    void SetItemIndex(unsigned int calc_index, unsigned int param_index, unsigned short index){calc_item[calc_index].calc_op[param_index].oprand.pre_item.pre_item_id = index;}

    //设置引用计算项的结果索引
    void SetItemResultIndex(unsigned int calc_index, unsigned int param_index, unsigned short result_index){calc_item[calc_index].calc_op[param_index].oprand.pre_item.result_id = result_index;}

    //设置数据输入类型
    void SetDataInputType(unsigned int calc_index, unsigned int param_index,unsigned int type){calc_item[calc_index].calc_op[param_index].oprand.data_input.data_input_type = type;}

    //设置数据输入的地址
    void SetDataInputAddr(unsigned int calc_index, unsigned int param_index,unsigned int addr){calc_item[calc_index].calc_op[param_index].oprand.data_input.data_input_addr = addr;}

    //更新任务的结果数 task_index:任务索引 返回0:失败或不是多结果任务; 其他:任务结果数
    unsigned int GetTaskMuchResultCount(unsigned int task_index);

    //判断任务是否是多结果的任务，返回：0:普通任务；1：多结果任务；
    int GetTaskTypeFlag(unsigned int index);


private:
    int step_index;
    unsigned int calc_item_count; /* 计算项的总数，最大 CALC_ITEM_NUM_MAX  */
    unsigned char calc_select_flag[CALC_ITEM_NUM_MAX]; /* 记录计算项是否选中，UI使用  */
    CALC_ITEM calc_item[CALC_ITEM_NUM_MAX];	/* Input结构体中存放不下，放在private中 */

};

#endif // CALCUATORDATA_H
