/**
  * @file  [IOInitGlobal.h]
  * @brief  IO配置的解析
  * @author  <th>
  * @date  <2017/7/4>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef IOINITGLOBAL_H
#define IOINITGLOBAL_H


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
 * @brief IO参数的解析
 * @param void
 * @return -1:失败; 0:成功;
 * @author <th>
 * @note
 */
int IO_Config_Init();

/**
 * @brief IO参数的保存
 * @param void
 * @return -1:失败; 0:成功;
 * @author <th>
 * @note 将IO参数按一定的格式保存成xml文件
 */
int IO_Config_Save();

/**
 * @brief 获取IO的脉冲宽度
 * @param index:IO索引; width:返回的脉冲宽度;
 * @return -1:失败; 0:成功;
 * @author <th>
 * @note
 */
int Get_IO_Width(int index, unsigned short* width );

/**
 * @brief 获取IO的高低电平有效标志
 * @param Flag:IO的高低电平有效标志;
 * @return void
 * @author <th>
 * @note
 */
void Get_IO_Valid_Flag(unsigned int *Flag);

/**
 * @brief 获取Flash的参数配置
 * @param width:Flash的脉冲宽度; Flag:Flash的高低电平有效标志;
 * @return void
 * @author <th>
 * @note
 */
void Get_Flash_Output_Param(unsigned int *width, unsigned int *Flag);

/**
 * @brief 获取IO触发的参数
 * @param index:IO索引; delay_time:触发延时时间; jitters_timer:滤波时间;
 * @return -1:失败; 0:成功;
 * @author <th>
 * @note
 */
int Get_IO_Trigger_Param(int index, float *delay_time, float *jitters_timer);

/**
 * @brief 设置IO的脉冲宽度
 * @param index:IO索引; width:设置的脉冲宽度;
 * @return -1:失败; 0:成功;
 * @author <th>
 * @note
 */
int Set_IO_Width(int index, unsigned short width );

/**
 * @brief 设置IO的高低电平有效标志
 * @param Flag:IO的高低电平有效标志;
 * @return void
 * @author <th>
 * @note
 */
void Set_IO_Valid_Flag(unsigned int Flag);

/**
 * @brief 设置Flash的参数配置
 * @param width:Flash的脉冲宽度; Flag:Flash的高低电平有效标志;
 * @return void
 * @author <th>
 * @note
 */
void Set_Flash_Output_Param(unsigned int width, unsigned int Flag);

/**
 * @brief 设置IO触发的参数
 * @param index:IO索引; delay_time:触发延时时间; jitters_timer:滤波时间;
 * @return -1:失败; 0:成功;
 * @author <th>
 * @note
 */
int Set_IO_Trigger_Param(int index, float delay_time, float jitters_timer);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif // IOINITGLOBAL_H

