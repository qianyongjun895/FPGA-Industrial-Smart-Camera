#ifndef PREBASICHEAD_H
#define PREBASICHEAD_H

typedef void (*Fun)(int,void *);
typedef struct
{
    Fun Set_ddr_enable;
    Fun Set_model_enable;
    Fun List_model_dlg;
    Fun SetPicSrc;
}STRUCT_FUN_PTR;

typedef enum
{
    RECTTOOL = 1, //矩形
    CIRCLETOOL,  //圆
    RINGTOOL,    //圆环
    POLYGONTOOL,  //多边形
    OTHERS
}TOOL_KIND;




#endif // PREBASICHEAD_H
