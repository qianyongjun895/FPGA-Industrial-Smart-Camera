/**
  * @file  [xmlInit.h]
  * @brief  初始化需要加载的库和函数指针,提供xml文件解析接口
  * @author  <th>
  * @date  <2017/5/12>
  * @version  <v1.0>
  * @note
  * 提供注册函数的初始化接口,保存UI需要的解析数据
  */

#ifndef __XML_INIT_H
#define __XML_INIT_H



#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#ifndef EQUAL_RETURN
#define EQUAL_RETURN(expression, z, ...)  if((expression))\
                                        {\
                                            return z;\
                                        }
#endif

#ifndef EQUAL_BREAK
#define EQUAL_BREAK(expression,  ...)  if((expression))\
                                        {\
                                            break;\
                                        }
#endif

#ifndef EQUAL_CONTINUE
#define EQUAL_CONTINUE(expression,  ...)  if((expression))\
                                        {\
                                            continue;\
                                        }
#endif

/**
 * @brief UI初始化数据,加载function库及函数
 * @param void
 * @return 0:解析完成  -1:解析失败
 * @author <th>
 * @note 保存UI需要的解析数据,根据解析结果加载任务对应的库,进行函数注册。
 */
extern int UI_Data_Init(void);

/**
 * @brief 获取任务类数量
 * @param void
 * @return 任务类数量
 * @author <th>
 * @note
 */
extern int Get_Task_Classify_Num(void);

/**
 * @brief 获取任务类名
 * @param index:数组下标,小于任务类数量; className[32]:返回任务类名,需判断是否为NULL
 * @return -1:数组下标即index越界; 其他:任务类的任务数量
 * @author <th>
 * @note
 */
extern void Get_Classify_Name(int index, char* className);

/**
 * @brief 获取任务类的Icon路径
 * @param index:数组下标,小于任务类数量; className[100]:返回任务类的Icon路径,需判断是否为NULL
 * @return -1:数组下标即index越界; 其他:任务类的任务数量
 * @author <th>
 * @note
 */
extern void Get_Classify_Icon_Path(int index, char* path);

/**
 * @brief 获取任务类的任务数量
 * @param index:数组下标,小于任务类数量;
 * @return -1:数组下标即index越界; 其他:任务类的任务数量
 * @author <th>
 * @note
 */
extern int Get_Classify_Task_Num(int index);

/**
 * @brief 获取任务功能对应的任务ID
 * @param class_index:数组下标,小于任务类数量; task_Index:数组下标,小于任务类的任务数量
 * @return -1:数组下标即index越界; 其他:任务ID
 * @author <th>
 * @note
 */
extern int Get_Classify_Task_ID(int class_index, int task_Index);

/**
 * @brief 获取黑白相机的任务加载标志
 * @param class_index:数组下标,小于任务类数量; task_Index:数组下标,小于任务类的任务数量
 * @return -1: 参数越界, 获取失败; 0:不加载;  1:加载
 * @author <th>
 * @note
 */
extern int Get_Black_Camera_Task_Load_Flag(int class_index, int task_Index);

/**
 * @brief 获取彩色相机的任务加载标志
 * @param class_index:数组下标,小于任务类数量; task_Index:数组下标,小于任务类的任务数量
 * @return -1: 参数越界, 获取失败; 0:不加载;  1:加载
 * @author <th>
 * @note
 */
extern int Get_Color_Camera_Task_Load_Flag(int class_index, int task_Index);

/**
 * @brief 获取任务的模板标志
 * @param class_index:数组下标,小于任务类数量; task_Index:数组下标,小于任务类的任务数量
 * @return -1: 参数越界, 获取失败; 0:无模板;  1:有模板
 * @author <th>
 * @note
 */
extern int Get_Task_Template_Flag(int class_index, int task_Index);

/**
 * @brief 获取任务的关联定位模块的加载标志
 * @param class_index:数组下标,小于任务类数量; task_Index:数组下标,小于任务类的任务数量
 * @return -1: 参数越界, 获取失败; 0:不加载;  1:加载
 * @author <th>
 * @note
 */
extern int Get_Task_Link_Module_Load_Flag(int class_index, int task_Index);

/**
 * @brief 获取任务的加速器模块数量
 * @param class_index:数组下标,小于任务类数量; task_Index:数组下标,小于任务类的任务数量
 * @return -1: 参数越界, 获取失败; 其他：任务的加速器模块数量
 * @author <th>
 * @note
 */
extern int Get_Task_Acce_Common_Module_Num(int class_index, int task_Index);

/**
 * @brief 获取任务说明
 * @param class_index:数组下标,小于任务类数量; task_Index:数组下标,小于任务类的任务数量; explain[1024]:任务说明
 * @return -1: 参数越界, 获取失败; 1：获取成功
 * @author <th>
 * @note
 */
extern int Get_Task_Explain(int class_index, int task_Index, char* explain);

/**
 * @brief 获取任务类的说明
 * @param index:数组下标,小于任务类数量;explain[512]:任务类的说明
 * @return -1: 参数越界, 获取失败; 1：获取成功
 * @author <th>
 * @note
 */
extern int Get_Classify_Explain(int index, char* explain);

/**
 * @brief 获取任务的加速器模块标志
 * @param class_index:数组下标,小于任务类数量; task_Index:数组下标,小于任务类的任务数量; Module_Index:加速器数组下标,小于任务的加速器模块数量
 * @return -1: 参数越界, 获取失败; 其他：加速器模块标志
 * @author <th>
 * @note
 */
extern int Get_Task_Acce_Common_Module_Flag(int class_index, int task_Index, int Module_Index);

/**
 * @brief 获取任务名字符串
 * @param index:数组下标,小于任务类数量;task_Index:数组下标,小于任务类的任务数量; taskName[32]:返回任务名字符串,需判断是否为NULL
 * @return
 * @author <th>
 * @note 如果taskName为NULL,表示数组下标即index越界。
 */
extern void Get_Classify_Task_Name(int class_index, int task_Index, char* taskName);

/**
 * @brief 获取任务对应的ui库的路径
 * @param index:数组下标,小于任务类数量;task_Index:数组下标,小于任务类的任务数量; LibraryName[100]:返回任务对应的ui库的路径,需判断是否为NULL
 * @return
 * @author <th>
 * @note 如果LibraryName为NULL,表示数组下标即index越界。
 */
extern void Get_UI_Library_Name(int class_index, int task_Index, char* LibraryName);

/**
 * @brief 获取任务对应的Icon路径
 * @param index:数组下标,小于任务类数量;task_Index:数组下标,小于任务类的任务数量; IconPath[100]:返回任务对应的Icon路径,需判断是否为NULL
 * @return
 * @author <th>
 * @note 如果IconPath为NULL,表示数组下标即index越界。
 */
extern void Get_Task_Icon_Path(int class_index, int task_Index, char* IconPath);

/**
 * @brief 获取任务对应的Function库的路径
 * @param index:数组下标,小于任务类数量;task_Index:数组下标,小于任务类的任务数量; LibraryName[100]:返回任务对应的Function库的路径,需判断是否为NULL
 * @return
 * @author <th>
 * @note 如果LibraryName为NULL,表示数组下标即index越界。
 */
extern void Get_Function_Library_Name(int class_index, int task_Index, char* LibraryName);

/**
 * @brief 获取任务的像素距离标志
 * @param Task_Id:任务类型ID;
 * @return -1:获取失败; 0:无像素距离; 1:有像素距离; 2:有长宽像素距离
 * @author <th>
 * @note
 */
extern int Get_Dist_Flag(int Task_Id);

/**
 * @brief 获取像素距离的结果ID
 * @param Task_Id:任务类型ID; Result_Index:长宽测量任务的距离索引值，从0开始，其他任务此值无效;
 * @return 结果ID,从0开始。 -1: 获取失败; 其他:结果ID
 * @author <th>
 * @note
 */
extern int Get_Dist_Result_ID(int Task_Id, int Result_Index);

/**
 * @brief 获取点、线任务的标志
 * @param Task_Id:任务类型ID;
 * @return -1: 其他任务类型; 0:点任务; 1:线任务
 * @author <th>
 * @note
 */
extern int Get_Point_Or_Line_Flag(int Task_Id);

/**
 * @brief 获取点、线任务的点线结果ID转换的UI显示的ID
 * @param Task_Id:任务类型ID; Result_Index:任务结果索引;
 * @return UI显示的点线ID,从1开始。 -1: 获取失败; 0: 普通任务，此值无效; 1<=:UI显示的ID
 * @author <th>
 * @note
 */
extern int Point_Or_Line_Result_Id_Change_UI_Id(int Task_Id, int Result_Index);

/**
 * @brief 获取点、线任务的点线结果ID
 * @param Task_Id:任务类型ID; Result_ID:多结果任务时填入结果索引,从1开始;普通任务时此值无效,可为任意合法的int型数据;
 * @return -1: 获取失败; 0<=:点、线任务的点线结果ID
 * @author <th>
 * @note
 */
extern int Get_Point_Or_Line_Result_Id(int Task_Id, int Result_Id);

/**
 * @brief 解析xmlFileName文件，返回xml文档指针
 * @param  xmlFileName:xml文件名(如果与执行文件不再同一目录下,需包含路径); XMLDocPtr:xml文档指针;
 * @return 0:解析完成  -1:解析失败
 * @author <th>
 * @note
 */
extern int Open_Xml_File(char* xmlFileName, void** XMLDocPtr);

/**
 * @brief 释放xml文档指针
 * @param  XMLDocPtr:xml文档指针;
 * @return void
 * @author <th>
 * @note
 */
extern void Free_Doc_Ptr(void *XMLDocPtr);

/**
 * @brief  获取xml文件的根节点
 * @param  doc:xml文档指针; root_Node:xml文件的根节点;
 * @return 0:获取成功  -1:获取失败
 * @author <th>
 * @note
 */
extern int Get_Doc_Root_Node(void* doc, void **root_Node);

/**
 * @brief  判断节点的名字是否正确
 * @param  node:节点; name:节点名;
 * @return 0:节点名符合  -1:节点名不符合
 * @author <th>
 * @note
 */
extern int Cmp_Node_Name(void* node, char* name);

/**
 * @brief  获取节点的子节点
 * @param  node:节点; child_node:子节点;
 * @return 0:获取成功  -1:获取失败
 * @author <th>
 * @note
 */
extern int Get_Current_Node_Child_Node(void* node, void **child_node);

/**
 * @brief  获取节点的兄弟节点
 * @param  node:节点,返回时是兄弟节点的指针;
 * @return 0:获取成功  -1:获取失败
 * @author <th>
 * @note
 */
extern int Get_Current_Node_Next_Node(void** node);

/**
 * @brief  获取节点的属性
 * @param  node:节点; Prop_name:属性名; prop:在该指针指向的内存中写入属性的内容;
 * @return 0:获取成功  -1:获取失败
 * @author <th>
 * @note
 */
extern int Get_Node_Prop(void* node, char* Prop_name, char* prop);

/**
 * @brief  获取节点的内容
 * @param  node:节点; text:在该指针指向的内存中写入节点的内容;
 * @return 0:获取成功  -1:获取失败
 * @author <th>
 * @note
 */
extern int Get_Node_Content(void* node, char* text);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
