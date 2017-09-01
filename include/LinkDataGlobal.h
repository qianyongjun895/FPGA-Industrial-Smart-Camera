/**
  * @file  [LinkDataGlobal.h]
  * @brief  关联关系及数据引用的管理
  * @author  <th>
  * @date  <2017/5/15>
  * @version  <v1.0>
  * @note
  *
  */

#ifndef LINKDATAGLOBAL_H
#define LINKDATAGLOBAL_H

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */


#define ARRAY_SIZE          100

#define Modbus_index                1  ///<modbus协议
#define Free_pro_index              2  ///<自定义协议
#define Calc_index                  3  ///<计算器
#define Cmp_jump_index              4  ///<比较跳转
#define Data_judge_index            5  ///<数据判断
#define Task_link_X_index           6  ///<关联数据X
#define Task_link_Y_index           7  ///<关联数据Y
#define Task_link_D_index           8  ///<关联数据角度
#define Stat_indedx                 9  ///<统计
#define Trend_indedx                10 ///<趋势
#define Todo_Protocol1_index        11 ///<未定义协议
#define Todo_Protocol2_index        12 ///<未定义协议
#define Todo_Task1_index            13 ///<未定义任务
#define Todo_Task2_index            14 ///<未定义任务
#define Todo_Task3_index            15 ///<未定义任务
#define Todo_Task4_index            16 ///<未定义任务

typedef struct{
  char Result_Name[ARRAY_SIZE];
}RESULT_NAME;
typedef struct {
    int TaskResultNum;
    RESULT_NAME *ResultName;
}TASK_RESULT_NAME;

/**  @brief  引用的ID转换的函数指针, 函数参数参考ResultId_Change_UIID函数  */
typedef int (*SW_ResultId_Change_UIId_Func)(int *result_count, int link_type_index, int task_type, unsigned int result_ID);

/**  @brief  引用的ID转换的函数指针, 函数参数参考UIId_Change_ResultID函数  */
typedef int (*SW_UIId_Change_ResultId_Func)(int link_type_index, int task_type, unsigned int rst_index, unsigned int UI_ID);

/**  @brief  关联定位的ID转换的函数指针, 函数参数参考AssociationMap_Change_TaskResultID函数  */
typedef int (*AM_UIId_Chang_ResultId_Func)(int task_type, int UI_Id, int link_type_index);

/**  @brief  关联定位的ID转换的函数指针, 函数参数参考AssociationMap_Change_UIID函数  */
typedef int (*AM_ResultId_Chang_UIId_Func)(int task_type, int result_Id, int link_type_index);




/**
 * @brief 初始化liblinkdata.so
 * @param void
 * @return -1:失败; 0:成功
 * @author <th>
 * @note
 */
extern int Init_Link_Data();

/**
 * @brief 获取任务名字符串
 * @param task_type:任务类型ID;
 *        taskName[40]:接收任务名字符串的数组地址
 * @return -1:失败; 0:成功
 * @author <th>
 * @note
 */
extern int Get_Task_Name(int task_index, char* taskName);

/**
 * @brief 根据任务类型判断是否是多结果任务
 * @param task_type:任务类型
 * @return 1:多结果任务; -1:不是多结果任务
 * @author <th>
 * @note
 */
extern int Get_Multi_Result_Task_Flag(int task_type);

/**
 * @brief 获取多结果任务的结果字符串
 * @param link_type_index:需要获取数据的任务类型宏定义，如：Modbus_index
 *        task_type:任务类型;
 *        result_count:多结果任务的结果数;
 *        Result_String[250]:接收字符串的数组
 * @return 填入Result_String数组的元素大小即填入了多少条字符串;
 * @author <th>
 * @note Result_String[250]这个字符串数组根据函数返回的大小取字符串显示
 */
extern int Get_Multi_Result_Task_Result_String(int link_type_index, int task_type, int result_count, RESULT_NAME* Result_Sting);

/**
 * @brief 查找对应任务类型的是否有link_type_index的数据
 * @param task_type:任务类型;
 *        link_type_index:需要获取数据的任务类型宏定义，如：Modbus_index
 * @return -1：获取失败;  0:该任务没有link_type_index的数据; 1:该任务有link_type_index的数据
 * @author <th>
 * @note
 */
extern int Get_Task_Link_Type_Flag(unsigned int task_type, int link_type_index);

/**
 * @brief 获取任务结果字符串
 * @param link_type_index:需要获取数据的任务类型宏定义，如：Modbus_index;
 *        task_type:任务类型ID;
 *        Multi_Result_Index:-1:不是多结果任务,0<: Multi_Result_Index的值对应 Get_Multi_Result_Task_Result_String 函数获取的字符串数组的下标+1
 *        result_ID:从0开始;
 *        str[100]:接收任务结果字符串的数组地址;
 * @return -1:该result_ID已经超过最大值,不能再获取该任务的结果字符串;
 *          0:该任务的result_ID任务结果不能被引用;
 *          1:本次获取成功,可继续获取任务结果字符串;
 * @author <th>
 * @note 如果Init_New_Quote_Change_Function或Init_New_AssociationMap_Change_Function被调用设置新的ID转换函数,
 *       并且link_type_index和Multi_Result_Index为-1，则将对返回的结果字符串不加限制，直到result_ID达到最大值。
 */
extern int Get_Task_Result_String(int link_type_index, int task_type, int Multi_Result_Index, int result_ID, char* str);

/**
 * @brief 查找任务的结果对应的数据类型
 * @param link_type_index:需要获取数据的任务类型宏定义,如:Modbus_index;
 *        task_type:任务类型;
 *        Multi_Result_Flag: -1:不是多结果任务, 0<:对应于Get_Multi_Result_Task_Result_String 函数获取的字符串数组的下标 + 1;
 *        result_ID:UI显示的ID,从1开始;
 * @return -1:没有找到任务结果对应的数据类型; 其他:任务结果对应的数据类型。
 * @author <th>
 * @note
 */
extern int Get_TaskResult_Type_Flag(int link_type_index, unsigned int task_type,  int Multi_Result_Flag, unsigned int result_ID);

/**
 * @brief 设置新的任务引用的ID转换函数
 * @param ChangeResultID:任务结果转换成UI界面显示的ID的函数指针;
 *        ChangeUIID:UI界面ID转换成任务结果ID的函数指针;
 * @return void
 * @author <th>
 * @note
 */
extern void Init_New_Quote_Change_Function(SW_ResultId_Change_UIId_Func ChangeResultID, SW_UIId_Change_ResultId_Func ChangeUIID);


/**
 * @brief 如果需要单独获取字符串进行显示，则需要调用函数进行转换
 * @param
 *        link_type_index:转换的任务标志索引,如Modbus_index;
 *        task_type:任务类型ID;
 *        result_count:-1:不是多结果任务, 0<:第*result_count个结果的索引;
 *        result_ID: ResultId_Change_UIID 函数的正确返回值;
 * @return -1:失败; 其他:可使用返回值调用 Get_Task_Result_String 函数获取单独的字符串进行显示
 * @author <th>
 * @note
 */
extern int UI_ID_Change_Array_Index(int link_type_index, int task_type, int result_count, unsigned int result_ID);
/**
 * @brief 任务结果转换成UI界面显示的ID
 * @param result_count:-1:不是多结果任务, 0<:第*result_count个结果的索引;
 *        link_type_index:转换的任务标志索引,如Modbus_index;
 *        task_type:任务类型ID;
 *        result_ID:任务结果ID;
 * @return  UI界面显示的ID索引(从1开始),返回-1并且*result_count==-1,没有该结果索引;
 *          如果返回-1,但是*result_count!=-1表示有该结果;但是它不包含其它结果;
 *          0:查找失败;
 * @author <th>
 * @note result_count -1的值对应 Get_Multi_Result_Task_Result_String 函数获取的字符串数组的下标
 */
extern int ResultId_Change_UIID(int *result_count, int link_type_index, int task_type, unsigned int result_ID);

/**
 * @brief UI界面ID转换成任务结果ID
 * @param link_type_index:转换的任务标志索引,如Modbus_index;
 *        task_type:任务类型ID;
 *        rst_index: -1:不是多结果任务, 0<:对应于 Get_Multi_Result_Task_Result_String 函数获取的字符串数组的下标 + 1;
 *        UI_ID:UI显示的ID,从1开始;
 * @return  任务结果ID; 返回-1:转换失败;
 * @author <th>
 * @note UI_ID:对应于从 Get_Task_Result_String 函数中获取的字符串索引。
 */
extern int UIId_Change_ResultID(int link_type_index, int task_type, unsigned int rst_index, unsigned int UI_ID);

/**
 * @brief  初始化关联相关的结果字符串
 * @param  task_type:任务类型ID
 *         result_count:如果任务是多结果任务,代表结果数量,否则该参数无意义。
 *         link_type_index:转换的任务标志索引,如Modbus_index;
 * @return -1:失败; 0<:关联相关的结果字符串数量
 * @author <th>
 * @note
 */
extern int Init_AssociationMap_Task_Result_String(int task_type, int result_count, int link_type_index);

/**
 * @brief 初始化后，根据array_index获取关联相关的结果字符串
 * @param array_index:数组下标，小于Init_AssociationMap_Task_Result_String函数返回值
 *        result_string:函数返回值正常时, 拷入关联相关的结果字符串
 * @return -1:失败; 0:成功
 * @author <th>
 * @note
 */
extern int Get_AssociationMap_Result_String(int array_index, RESULT_NAME* result_string);

/**
 * @brief 设置新的关联定位的ID转换函数
 * @param ChangeResultID:任务结果转换成UI界面显示的ID的函数指针;
 *        ChangeUIID:UI界面ID转换成任务结果ID的函数指针;
 * @return void
 * @author <th>
 * @note
 */
extern void Init_New_AssociationMap_Change_Function(AM_ResultId_Chang_UIId_Func ChangeResultID, AM_UIId_Chang_ResultId_Func ChangeUIID);

/**
 * @brief 关联定位模块将任务结果ID转换为UI的ID
 * @param task_type:任务类型ID;
 *        result_ID:任务结果ID;
 *        link_type_index:转换的任务标志索引,如Modbus_index;
 * @return UI的ID(从1开始)
 * @author <th>
 * @note
 */
extern int AssociationMap_Change_UIID(int task_type, int result_ID, int link_type_index);

/**
 * @brief 关联定位模块将UI的ID转换为任务结果ID
 * @param task_type:任务类型ID;
 *        UI_ID:UI显示的ID,从1开始;
 *        link_type_index:转换的任务标志索引,如Modbus_index;
 * @return -1: 转换失败或参数越界; 0=<: 任务结果ID
 * @author <th>
 * @note
 */
extern int AssociationMap_Change_TaskResultID(int task_type, int UI_ID, int link_type_index);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif // LINKDATAGLOBAL_H
