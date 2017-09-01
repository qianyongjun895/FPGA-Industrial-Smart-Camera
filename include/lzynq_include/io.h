#ifndef __IO_H_
#define __IO_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define INPUT_PIN0_MASK		0x1
#define INPUT_PIN1_MASK		0x2
#define OUTPUT_PIN_0		0x1
#define OUTPUT_PIN_1		0x2
#define OUTPUT_PIN_2		0x4
#define OUTPUT_PIN_3		0x8
/** IO寄存器 */
#define GPIO_CTRL_IN_REG	0x1083	///<  相机外部GPIO输入寄存器
#define GPIO_CTRL_IN_MASK	0x3     ///<  相机外部GPIO输入掩码

#define GPIO_CTRL_OUT_REG               0x091       ///<  相机外部GPIO输出寄存器
#define GPIO_CTRL_OUT_MASK              0xf         ///<  相机外部GPIO输出掩码，必须在gpio_out_vld有效
#define FLASH_CTRL_OUT_MASK             0x10000     ///<  相机控制闪光灯输出掩码，必须在flash_out_vld有效
#define GPIO_CTRL_OUT_VLD_REG           0x092       ///<  GPIO输出寄存器
#define GPIO_CTRL_OUT_VLD_MASK          0xf         ///<  1=GPIO输出使能掩码
#define GPIO_CTRL_OUT_REV_VLD_MASK      0xf0000000	///<  1=GPIO输出使能反向掩码
#define FLASH_CTRL_OUT_VLD_MASK         0x10000     ///<  相机控制闪光灯输出使能掩码
#define FLASH_CTRL_OUT_REVERSE_MASK     0x1000000	///<  相机控制闪光灯输出反向掩码
#define FLASH_CTRL_OUT_DELAY_TIMER_REG	0x093       ///<  闪光灯输出，保持时间，计时完成自动恢复1
#define GPIO_CTRL_OUT_0_HOLD_TIMER_REG	0x094       ///<  GPOI_0输出，保持时间，计时完成自动恢复1
#define GPIO_CTRL_OUT_1_HOLD_TIMER_REG	0x095       ///<  GPOI_1输出，保持时间，计时完成自动恢复1
#define GPIO_CTRL_OUT_2_HOLD_TIMER_REG	0x096       ///<  GPOI_2输出，保持时间，计时完成自动恢复1
#define GPIO_CTRL_OUT_3_HOLD_TIMER_REG	0x097       ///<  GPOI_3输出，保持时间，计时完成自动恢复1

#define GPIO_CTRL_IN_0_JITTERS_TIMER_REG	0x098	///<  GPOI_0输入，滤波时间
#define GPIO_CTRL_IN_0_DELAY_TIMER_REG	    0x099	///<  GPOI_0输入，延时时间
#define GPIO_CTRL_IN_1_JITTERS_TIMER_REG	0x09A	///<  GPOI_1输入，滤波时间
#define GPIO_CTRL_IN_1_DELAY_TIMER_REG	    0x09B	///<  GPOI_1输入，延时时间

#define GPIO_CTRL_OUT_0_DELAY_TIMER_REG	    0x09C	///<  GPOI_1输入，延时时间
#define GPIO_CTRL_OUT_1_DELAY_TIMER_REG	    0x09D	///<  GPOI_1输入，延时时间
#define GPIO_CTRL_OUT_2_DELAY_TIMER_REG	    0x09E	///<  GPOI_1输入，延时时间
#define GPIO_CTRL_OUT_3_DELAY_TIMER_REG	    0x09F	///<  GPOI_1输入，延时时间

/** @brief IO输入触发的四种模式 */
#define RISE_EDGE_TRIGGER	1
#define FALL_EDGE_TRIGGER	2
#define HIGH_LEVEL_TRIGGER	3
#define LOW_LEVEL_TRIGGER	4

typedef struct {
    unsigned int IO_sum;	//io口数量
    unsigned short width[32];	// TimeOut[0] 表示IO1的输出脉冲宽
    unsigned int IO_valid_flag;//输出高电平有效（1），低电平有效（0）
}IO_OUTPUT_CONFIG;

typedef struct{
    unsigned int flash_width;//闪光灯输出宽度
    unsigned int flash_valid_flag;//闪光灯输出高电平有效（1），低电平有效（0）
}FLASH_OUTPUT_CONFIG;

typedef struct{
    float IO1_delay;
    float IO2_delay;
    float IO1_jitters_timer;
    float IO2_jitters_timer;
}IO_TRIGGER_CONFIG;



/**
 * @brief IO_Input_Get
 * @param index
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 获取IO输入
 */
int IO_Input_Get(int index);

/**
 * @brief IO_Output_Set
 * @param bitmask
 * @author Vincent
 * @date 2017/5/12
 * @note IO输出设置
 */
void IO_Output_Set(unsigned int bitmask);

/**
 * @brief Flash_Output_Set
 * @author Vincent
 * @date 2017/5/12
 * @note Flash输出设置
 */
void Flash_Output_Set(void);

/**
 * @brief IO_Output_Pulse_Width_Set
 * @param index: IO口索引号
 * @param width: 1000表示20us, 50000表示1ms
 * @author Vincent
 * @date 2017/5/12
 * @note IO输出脉冲宽度设置
 */
void IO_Output_Pulse_Width_Set(int index, int width);

/**
 * @brief IO_Tigger_Jitters_Set
 * @param index
 * @param jetters
 * @author pml
 * @date 2017/5/12
 * @note 设置IO触发滤波寄存器
 */
void IO_Tigger_Jitters_Set(int index, int jetters);

/**
 * @brief IO_Trigger_Delay_Time_Set
 * @param index
 * @param delay_time
 * @author pml
 * @date 2017/5/12
 * @note 设置IO触发延时寄存器
 */
void IO_Trigger_Delay_Time_Set(int index, int delay_time);

/**
 * @brief IO_Tigger_Test_Init
 * @param trigger_mode
 * @author pml
 * @date 2017/5/12
 * @note IO触发测试初始化，在调触发测试之前调用
 */
void IO_Tigger_Test_Init(int trigger_mode);

/**
 * @brief IO_Trigger_Test
 * @param input_mask
 * @return
 * @author pml
 * @date 2017/5/12
 * @note IO触发测试，0：表示没触发成功，其他：返回触发成功的类型
 */
int IO_Trigger_Test(int input_mask);



/**
 * @brief IO_Output_Config_Set
 * @param pIOOutputConfig
 * @author pml
 * @date 2017/5/12
 * @note 设置IO输出配置
 */
void IO_Output_Config_Set(IO_OUTPUT_CONFIG *pIOOutputConfig);

/**
 * @brief IO_Output_Config_Get
 * @param pIOOutputConfig
 * @author pml
 * @date 2017/5/12
 * @note 获取IO输出配置
 */
void IO_Output_Config_Get(IO_OUTPUT_CONFIG * pIOOutputConfig);

/**
 * @brief Flash_Output_Config_Set
 * @param pFlashConfig
 * @author pml
 * @date 2017/5/12
 * @note 设置Flash输出配置
 */
void Flash_Output_Config_Set(FLASH_OUTPUT_CONFIG *pFlashConfig);

/**
 * @brief Flash_Output_Config_Get
 * @param pFlashConfig
 * @author pml
 * @date 2017/5/12
 * @note 获取Flash输出配置
 */
void Flash_Output_Config_Get(FLASH_OUTPUT_CONFIG * pFlashConfig);


/**
 * @brief IO_Trigger_Config_Set
 * @param pIOTriggerConfig
 * @author pml
 * @date 2017/5/12
 * @note 设置IO触发配置
 */
void IO_Trigger_Config_Set(IO_TRIGGER_CONFIG *pIOTriggerConfig);

/**
 * @brief IO_Trigger_Config_Load
 * @param pIOTriggerConfig
 * @author pml
 * @date 2017/5/12
 * @note 获取IO触发配置
 */
void IO_Trigger_Config_Get(IO_TRIGGER_CONFIG * pIOTriggerConfig);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif

