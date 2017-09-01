/**
  * @file  [BaseStruct.h]
  * @brief  定义一些公共的结构体
  * @author  <Terry>
  * @date  <2017/5/15>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef _BASE_STRUCT_H_
#define _BASE_STRUCT_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#define TASK_STEP_MAX 250
#define DETECT_OK 	1
#define DETECT_NG 	0
#define DBL_EPSILON     2.2204460492503131e-16
#define FLT_EPSILON     1.192092896e-07F
#define DBL_MAX 1.7976931348623158e+308
#define FLT_MAX 3.4028235E+38
#define DEG_PER_THETA	57.295779513082320876798154814105
#define THETA_PER_DEG	0.0174532925199432957692369076849

typedef struct
{
    double theta;
    double degree;
    double rotate_deg; /* 旋转角度 */
    double cos;
    double sin;
    double x;
    double y;
    double phy_x;
    double phy_y;
} LineParameter;

typedef struct {
    short x_s;
    short y_s;
}POINT_S;

typedef struct {
    int x_i;
    int y_i;
}POINT_I;

typedef struct {
    float x_f;
    float y_f;
}POINT_F;

/** @brief 颜色选择枚举 */
typedef enum {
    COLOR_RED = 0,      ///< 红
    COLOR_ORANGE,       ///< 橙
    COLOR_YELLOW,       ///< 黄
    COLOR_GREEN,        ///< 绿
    COLOR_BLUE,         ///< 蓝
    COLOR_CYAN,         ///< 靛
    COLOR_PURPLE,       ///< 紫
    COLOR_WHILTE,       ///< 白
    COLOR_BLACK,        ///< 黑
    COLOR_GRAY,         ///< 灰
} COLORSELECT;

typedef struct {
    POINT_F center;
    double r;
}CIRCLE;

typedef struct {
    double distance;	/* 设置模板时两点之间距离 */
    double theta;	/* 设置模板时两点之间形成的角度 */
}ROTATE_PARA;

/* struct */
typedef struct OSD_CIRCLE{
    unsigned int x;
    unsigned int y;
    unsigned int r;
    unsigned int color;
}OSD_CIRCLE, *pOSD_CIRCLE;

typedef struct OSD_RECT{
    unsigned int x0;
    unsigned int y0;
    unsigned int x1;
    unsigned int y1;
    unsigned int color;
}OSD_RECT, *pOSD_RECT;

typedef struct OSD_LINE{
    unsigned int x0;
    unsigned int y0;
    unsigned int x1;
    unsigned int y1;
    unsigned int color;
}OSD_LINE, *pOSD_LINE;

typedef struct OSD_ARC{
    int x;
    int y;
    int r;
    int color;
    double angStart;
    double angEnd;
}OSD_ARC,*pOSD_ARC;

typedef struct OSD_POLYGON{
    POINT_I Polygon[8];
    unsigned int vertex_count;
    unsigned int color;
}OSD_POLYGON, *pOSD_POLYGON;

typedef struct {
    unsigned short x;
    unsigned short y;
    unsigned int degree;
} EDGE_POINT;
/**
  * @struct <OSD_ATTRIBUTE>
  * @brief OSD属性
  */
typedef struct {
    unsigned char osd_color;       ///< osd颜色
    unsigned char osd_width;       ///< osd粗细
} OSD_ATTRIBUTE;

/**
  * @struct <OSD_CONFIG>
  * @brief 添加新的成员需要在TaskStepHeadInit函数里面初始化粗细
  */
typedef struct {
    OSD_ATTRIBUTE image_border_osd;   ///< 图像边界OSD
    OSD_ATTRIBUTE param_edit_osd;     ///< 参数编辑界面OSD
    OSD_ATTRIBUTE checked_osd;        ///< 选中OSD
    OSD_ATTRIBUTE calc_osd;           ///< 计算/取样后OSD
    OSD_ATTRIBUTE edge_point_osd;     ///< 边沿点OSD
    OSD_ATTRIBUTE area_select_osd;    ///< 区域筛选OSD
} OSD_CONFIG;

#define TASK_RESULT_VALID_FLAG  	0x5a ///< 任务结果有效
#define TASK_RESULT_INVALID_FLAG	0x0 ///< 任务结果无效

#define DATA_SINT           0 ///< 有符号整型数据
#define DATA_SINT_INV       1 ///< 有符号整型数据反转
#define DATA_UINT           2 ///< 无符号整型数据
#define DATA_UINT_INV       3 ///< 无符号整型数据反转
#define DATA_FLT            4 ///< 浮点型数据
#define DATA_FLT_INV        5 ///< 浮点型数据反转
#define DATA_LONG           6 ///< 长整型数据
#define DATA_LONG_INV       7 ///< 长整型数据反转
#define DATA_DBL            8 ///< 双精度型数据
#define DATA_DBL_INV        9 ///< 双精度型数据反转

/** @union <RESULTvalue>
 *  @brief 结果数据类型的联合体
*/
typedef union {
    int I32_Value; 						///< 有符号整型数据
    int I32_Value_Revert;				///< 有符号整型数据反转
    unsigned int U32_Value; 			///< 无符号整型数据
    unsigned int U32_Value_Revert; 		///< 无符号整型数据反转
    float F32_Value; 					///< 浮点型数据
    float F32_Value_Revert; 			///< 浮点型数据反转
    double D64_Value; 					///< 双精度型数据
    double D64_Value_Revert; 			///< 双精度型数据反转
} RESULTvalue;

/** @struct <RST_VALUE_STRUCT>
 *  @brief 结果数据结构体
*/
typedef struct {
    unsigned int resultflag;			///< 结果数据是否有效的标志
    unsigned int resulttype;			///< RESULTvalue 联合体中的数据类型
    RESULTvalue  value;         		///< 结果数据
} RST_VALUE_STRUCT;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
