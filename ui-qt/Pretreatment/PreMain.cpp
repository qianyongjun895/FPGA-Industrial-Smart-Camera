#include <qdebug.h>
#include "PreMain.h"
#include "ui_PreMain.h"
#include <QMessageBox>
#include "ColorSelect/CGetImageThread.h"
#include "../../Global/UtilitiesFun.h"
#include "PretreatMentListCollect/PretreatmentSummaryDialog.h"
#include "PretreatmentModuleItem.h"
#include "AcceCommon.h"
#include "AreaSelect/AreaSelectDialog.h"
#include "BinaryzationModule/BinaryzationDlg.h"
#include "ColorSelect/ColorSelectDialog.h"
#include "EdgeExtract/EdgeExtractDlg.h"
#include "SkeletonThreshold/SkeletonThresholdDlg.h"
#include "ImgpreprocessModule/ImagepreprocessDlg.h"
#include "GrayHistogram/GrayHistogramDialog.h"
#include "Cpt/CptDlg.h"
#include "cmos_common.h"
//#include "System.h"

int acce_valid_src[64][64] = {
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 }, //0
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 }, //1
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 }, //2
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 }, //3
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 }, //4
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 }, //5
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//6
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 } ,//7
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },  //8
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//9
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//10
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//11
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//12
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//13
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//14
    //缺陷提取
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 } ,//15
    //实时浓淡补正
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 }, //16

    {1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,1,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//17
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//18
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//19
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//20
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//21
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//22
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 } ,//23
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 }, //24
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//25
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//26
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//27
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//28
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//29
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//30
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 } ,//31
    //二值化处理模块
    {1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,1,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 }, //32
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//33
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//34
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//35
    //轮廓
    {1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,1,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//36
    //边沿提取
    {1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,1,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     1,0,0,0, 0,0,0,0, 0,1,1,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//37
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//38
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 } ,//39
    //连通域
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     1,0,0,0, 0,0,0,0, 0,0,1,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 }, //40
    //色彩提取
    {1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//41
    //区域筛选
    {1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,1,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//42
    //灰度直方图
    {1,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,1,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     1,0,0,0, 0,0,0,0, 0,0,1,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//43
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//44
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//45
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//46
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 } ,//47
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 }, //48

    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//49
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//50
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//51
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//52
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//53
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//54
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 } ,//55
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 }, //56

    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//57
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//58
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//59
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//60
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//61
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 },//62
    {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
     0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0,  0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 } ,//63
};
//cpt
void SetCptEnable(int flag,void *Pdata)
{
     PreMain *p_main = (PreMain*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)p_main->m_pre_ptr;
    if(ptr == NULL)
        return;
    if(flag == 1)
    {
        ptr->image_acce_param.cpt_model_cfg.model_enable =1;
        AcceleratorModuleEnable(ACCE_CPT_MODEL_ID);

    }else
    {
        ptr->image_acce_param.cpt_model_cfg.model_enable =0;
        AcceleratorModuleDisable(ACCE_CPT_MODEL_ID);
    }
}
void SetCptDDREnable(int flag,void *Pdata)
{
    PreMain *p_main = (PreMain*)Pdata;
    AcceleratorModuleWriteDdrCfg(ACCE_CPT_MODEL_ID,p_main->m_step,flag);
}
void ListCptDlg(int itaskKind,void *Pdata)
{
    PreMain *p_main = (PreMain*)Pdata;
    CptDlg dlg;
    dlg.m_task_id = p_main->m_task_id;
    dlg.m_step = p_main->m_step;
    dlg.m_pre_ptr = p_main->m_pre_ptr;
    dlg.pen = p_main->m_pen_color;
    dlg.IniData();
    dlg.exec();
    p_main->SetDDRPicLimit();
}

//图像预处理转换模块使能
void SetPreEnable(int flag,void *Pdata)
{
    PreMain *p_main = (PreMain*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)p_main->m_pre_ptr;
    if(ptr == NULL)
        return;
    if(flag == 1)
    {
        ptr->image_acce_param.pre_model_cfg.model_enable = 1;
        AcceleratorModuleEnable(ACCE_PRE_MODEL_ID);
    }else
    {
        ptr->image_acce_param.pre_model_cfg.model_enable = 0;
        AcceleratorModuleDisable(ACCE_PRE_MODEL_ID);
    }
}
//图像预处理转换界面显示
void ListPreDlg(int itaskKind,void *Pdata)
{
    PreMain *p_main = (PreMain*)Pdata;
    ImagepreprocessDlg dlg;
    dlg.m_step = p_main->m_step;
    dlg.m_task_id = p_main->m_task_id;
    dlg.m_pre_ptr = p_main->m_pre_ptr;
    dlg.IniData();
    dlg.exec();

}
//图像预处理转换出图DDR使能
void SetPreDDREnable(int flag,void *Pdata)
{
    PreMain *p_main = (PreMain*)Pdata;
    AcceleratorModuleWriteDdrCfg(ACCE_PRE_MODEL_ID,p_main->m_step,flag);
}
void SetPreSrcValue(int taskId,void *Pdata)
{
    PreMain *p_main = (PreMain*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)p_main->m_pre_ptr;
    if(ptr == NULL)
        return;
    ptr->image_acce_param.pre_model_cfg.pre_src_in_sel= taskId;

    AcceleratorModuleConfig(ACCE_PRE_MODEL_ID,p_main->m_step);
}
//二值化处理模块使能
void SetBWProcEnable(int flag,void *Pdata)
{
    PreMain *p_main = (PreMain*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)p_main->m_pre_ptr;
    if(ptr == NULL)
        return;
    if(flag == 1)
    {
        ptr->image_acce_param.bw_proc_model_cfg.model_enable =1;
        AcceleratorModuleEnable(ACCE_BW_PROC_MODEL_ID);

    }else
    {
        ptr->image_acce_param.bw_proc_model_cfg.model_enable =0;
        AcceleratorModuleDisable(ACCE_BW_PROC_MODEL_ID);
    }
}
//二值化处理模块界面显示
void ListBWProcDlg(int itaskKind,void *Pdata)
{
    PreMain *p_main = (PreMain*)Pdata;
    BinaryzationDlg dlg;
    dlg.m_step = p_main->m_step;
    dlg.m_task_id =p_main->m_task_id;
    dlg.m_pre_ptr = p_main->m_pre_ptr;
    dlg.m_listX = p_main->m_listX;
    dlg.m_listY = p_main->m_listY;
    dlg.IniData();
    dlg.exec();
}
//二值化处理模块出图DDR使能
void SetBWProcDDREnable(int flag,void *Pdata)
{
    PreMain *p_main = (PreMain*)Pdata;
    AcceleratorModuleWriteDdrCfg(ACCE_BW_PROC_MODEL_ID,p_main->m_step,flag);
}
void SetBWSrcValue(int taskId,void *pData)
{
    PreMain *p_main = (PreMain*)pData;
    ACCE_MODEL *ptr = (ACCE_MODEL*)p_main->m_pre_ptr;
    if(ptr == NULL)
        return;
    ptr->image_acce_param.bw_proc_model_cfg.bw_proc_src_in = taskId;

    AcceleratorModuleConfig(ACCE_BW_PROC_MODEL_ID,p_main->m_step);
}
//轮廓匹配模块使能
void SetSkeMatchProcEnable(int flag,void *Pdata)//轮廓匹配
{
    PreMain *p_main = (PreMain*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)p_main->m_pre_ptr;
    if(ptr == NULL)
        return;
    if(flag == 1)
    {
        ptr->image_acce_param.match_model_cfg.model_enable =1;
        AcceleratorModuleEnable(ACCE_SKE_MATCH_MODLE_ID);

    }else
    {
        ptr->image_acce_param.match_model_cfg.model_enable =0;
        AcceleratorModuleDisable(ACCE_SKE_MATCH_MODLE_ID);

    }
}
//轮廓匹配界面显示
void ListSkeMatchProcDlg(int itaskKind,void *Pdata)
{
    /*PreMain *p_main = (PreMain*)Pdata;
    SkeletonThresholdDlg dlg;
    dlg.m_step = p_main->m_step;
    dlg.m_task_id = p_main->m_task_id;
    dlg.m_pre_ptr = p_main->m_pre_ptr;
    dlg.m_listX = p_main->m_listX;
    dlg.m_listY = p_main->m_listY;
    dlg.move(660,0);
    dlg.exec();*/

}
//轮廓匹配DDR使能
void SetSkeMatchProcDDREnable(int flag,void *Pdata)
{
    PreMain *p_main = (PreMain*)Pdata;
    AcceleratorModuleWriteDdrCfg(ACCE_SKE_MATCH_MODLE_ID,p_main->m_step,flag);
}
void SetSkeMatchProcSrcValue(int taskId,void *pData)
{
    PreMain *p_main = (PreMain*)pData;
    ACCE_MODEL *ptr = (ACCE_MODEL*)p_main->m_pre_ptr;
    if(ptr == NULL)
        return;
    ptr->image_acce_param.match_model_cfg.match_src_sel= taskId;

    AcceleratorModuleConfig(ACCE_SKE_MATCH_MODLE_ID,p_main->m_step);
}
//边沿提取模块使能
void SetEdgeExtractEnable(int flag,void *Pdata) //边沿提取
{
    PreMain *p_main = (PreMain*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)p_main->m_pre_ptr;
    if(ptr == NULL)
        return;
    if(flag == 1)
    {
        ptr->image_acce_param.side_sel_model_cfg.model_enable =1;
        AcceleratorModuleEnable(ACCE_EDGE_EXTRACT_MODLE_ID);
    }else
    {
        ptr->image_acce_param.side_sel_model_cfg.model_enable =0;
        AcceleratorModuleDisable(ACCE_EDGE_EXTRACT_MODLE_ID);
    }
}
//边沿提取界面显示
void ListEdgeExtractDlg(int itaskKind,void *Pdata)
{
    PreMain *p_main = (PreMain*)Pdata;
    EdgeExtractDlg dlg;
    dlg.m_step = p_main->m_step;
    dlg.m_task_id = p_main->m_task_id;
    dlg.m_pre_ptr = p_main->m_pre_ptr;
    dlg.m_listX = p_main->m_listX;
    dlg.m_listY = p_main->m_listY;
    dlg.InitData();
    dlg.move(660,0);
    p_main->ConnectEdgePointSlot(&dlg);
    dlg.exec();
    p_main->DisConnectEdgePointSlot(&dlg);
}
//边沿提取DDR使能
void SetEdgeExtractDDREnable(int flag,void *Pdata)
{
    PreMain *p_main = (PreMain*)Pdata;
    AcceleratorModuleWriteDdrCfg(ACCE_EDGE_EXTRACT_MODLE_ID,p_main->m_step,flag);
}
void SetEdgeExtractSrcValue(int taskId,void *pData)
{
    PreMain *p_main = (PreMain*)pData;
    ACCE_MODEL *ptr = (ACCE_MODEL*)p_main->m_pre_ptr;
    if(ptr == NULL)
        return;
    ptr->image_acce_param.side_sel_model_cfg.side_sel_src_sel= taskId;

    AcceleratorModuleConfig(ACCE_EDGE_EXTRACT_MODLE_ID,p_main->m_step);
}
//连通域模块使能
void SetConnectEnable(int flag,void *Pdata) //连通域
{
    PreMain *p_main = (PreMain*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)p_main->m_pre_ptr;
    if(ptr == NULL)
        return;
    if(flag == 1)
    {
        ptr->image_acce_param.link_model_cfg.model_enable =1;
        AcceleratorModuleEnable(ACCE_CONNECT_REGION_MODLE_ID);

    }else
    {
        ptr->image_acce_param.link_model_cfg.model_enable =0;
        AcceleratorModuleDisable(ACCE_CONNECT_REGION_MODLE_ID);
    }
}
//连通域模块界面显示
void ListConnectDlg(int itaskKind,void *Pdata)
{

}
//连通域模块DDR使能
void SetConnectDDREnable(int flag,void *Pdata)
{
    PreMain *p_main = (PreMain*)Pdata;
    AcceleratorModuleWriteDdrCfg(ACCE_CONNECT_REGION_MODLE_ID,p_main->m_step,flag);
}
void SetConnectSrcValue(int taskId,void *pData)
{
    PreMain *p_main = (PreMain*)pData;
    ACCE_MODEL *ptr = (ACCE_MODEL*)p_main->m_pre_ptr;
    if(ptr == NULL)
        return;
    ptr->image_acce_param.link_model_cfg.link_src_sel= taskId;

    AcceleratorModuleConfig(ACCE_CONNECT_REGION_MODLE_ID,p_main->m_step);
}
//色彩提取模块使能
void SetColorExtractEnable(int flag,void *Pdata) //色彩提取
{
    PreMain *p_main = (PreMain*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)p_main->m_pre_ptr;
    if(ptr == NULL)
        return;
    if(flag == 1)
    {
        ptr->image_acce_param.color_draw_model_cfg.model_enable =1;
        AcceleratorModuleEnable(ACCE_COLOR_EXTRACT_MODLE_ID);

    }else
    {
        ptr->image_acce_param.color_draw_model_cfg.model_enable =0;
        AcceleratorModuleDisable(ACCE_COLOR_EXTRACT_MODLE_ID);

    }
}
//色彩提取模块界面显示
void ListColorExtractDlg(int itaskKind,void *Pdata)
{
    PreMain *p_main = (PreMain*)Pdata;
    ColorSelectDialog dlg;
    dlg.m_step = p_main->m_step;
    dlg.m_color_task_id = p_main->m_task_id;
    dlg.m_pre_ptr = p_main->m_pre_ptr;
    dlg.IniData();
    dlg.exec();
}
//色彩提取模块DDR使能
void SetColorExtractDDREnable(int flag,void *Pdata)
{
    PreMain *p_main = (PreMain*)Pdata;
    AcceleratorModuleWriteDdrCfg(ACCE_COLOR_EXTRACT_MODLE_ID,p_main->m_step,flag);
}
void SetColorExtractSrcValue(int taskId,void *pData)
{
    /*PreMain *p_main = (PreMain*)pData;
     ACCE_MODEL *ptr = (ACCE_MODEL*)p_main->m_pre_ptr;
     if(ptr == NULL)
         return;
     ptr->image_acce_param.color_draw_model_cfg.zone_sel= taskId;
     AcceleratorModuleConfig(ACCE_COLOR_EXTRACT_MODLE_ID,m_step);*/


}
//区域选择模块使能
void SetAreaSelectEnable(int flag,void *Pdata)//区域选择
{
    PreMain *p_main = (PreMain*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)p_main->m_pre_ptr;
    if(ptr == NULL)
        return;
    if(flag == 1)
    {
        ptr->image_acce_param.select_model_cfg.model_enable =1;
        AcceleratorModuleEnable(ACCE_AREA_SELECT_MODEL_ID);

    }else
    {
        ptr->image_acce_param.select_model_cfg.model_enable =0;
        AcceleratorModuleDisable(ACCE_AREA_SELECT_MODEL_ID);
    }
}
//区域选择模块界面显示
void ListAreaSelectDlg(int itaskKind,void *Pdata)
{
    PreMain *p_main = (PreMain*)Pdata;
    AreaSelectDialog dlg;
    dlg.m_step = p_main->m_step;
    dlg.m_color_select_task_id = p_main->m_task_id;
    dlg.m_pre_ptr = p_main->m_pre_ptr;
    dlg.pen = p_main->m_pen_color;
    dlg.IniData();
    dlg.exec();
}
//区域选择模块DDR使能
void SetAreaSelectDDREnable(int flag,void *Pdata)
{
    PreMain *p_main = (PreMain*)Pdata;
    AcceleratorModuleWriteDdrCfg(ACCE_AREA_SELECT_MODEL_ID,p_main->m_step,flag);
}
void SetAreaSelectSrcValue(int taskId,void *pData)
{
    PreMain *p_main = (PreMain*)pData;
    ACCE_MODEL *ptr = (ACCE_MODEL*)p_main->m_pre_ptr;
    if(ptr == NULL)
        return;
    ptr->image_acce_param.select_model_cfg.select_src_sel= taskId;

    AcceleratorModuleConfig(ACCE_AREA_SELECT_MODEL_ID,p_main->m_step);
}
//直方图
void ListGrayHistogramDlg(int itaskKind,void *Pdata)
{
    PreMain *p_main = (PreMain*)Pdata;
    GrayHistogramDialog dlg;
    dlg.m_step_id = p_main->m_step;
    dlg.m_task_id= p_main->m_task_id;
    dlg.m_pre_ptr = p_main->m_pre_ptr;
    dlg.IniData();
    dlg.exec();
}
void SetGrayHistogramEnable(int flag,void *Pdata)
{
    PreMain *p_main = (PreMain*)Pdata;
    ACCE_MODEL *ptr = (ACCE_MODEL*)p_main->m_pre_ptr;
    if(ptr == NULL)
        return;
    if(flag == 1)
    {
        ptr->image_acce_param.hist_model_cfg.model_enable = 1;
        AcceleratorModuleEnable(ACCE_HIST_MODEL_ID);
    }else
    {
        ptr->image_acce_param.hist_model_cfg.model_enable = 0;
        AcceleratorModuleDisable(ACCE_HIST_MODEL_ID);
    }
}
void SetGrayHistogramDDREnable(int flag,void *Pdata)
{
    PreMain *p_main = (PreMain*)Pdata;
    AcceleratorModuleWriteDdrCfg(ACCE_HIST_MODEL_ID,p_main->m_step,flag);
}
void SetGrayHistogramSrcValue(int taskId,void *pData)
{

    PreMain *p_main = (PreMain*)pData;
    ACCE_MODEL *ptr = (ACCE_MODEL*)p_main->m_pre_ptr;
    if(ptr == NULL)
        return;
    ptr->image_acce_param.hist_model_cfg.hist_stat_src_sel= taskId;

    AcceleratorModuleConfig(ACCE_HIST_MODEL_ID,p_main->m_step);
}
PreMain::PreMain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreMain)
{
    ui->setupUi(this);
    InitFunPtr();
    m_pre_ptr = NULL;
    m_timer = new QTimer;
    connect(m_timer,&QTimer::timeout,this,&PreMain::Time_Out);
    connect(this,&PreMain::PointChangeSignal,ui->labelPic,&LabelMain::paintPointSlot);

    /*for(int i =0; i<64;i++)
    {
        for(int j= 0;j<64;j++)
        {
            acce_valid_src[i][j]=1;
        }
    }*/
    ListInfo("图像加速器模块设定适用于图像处理的预处理种类，指定了复数个种类，以从上往方下的方式进行处理");

}
PreMain::~PreMain()
{
    if(m_timer !=NULL)
    {
        delete m_timer;
        m_timer = NULL;
    }
    disconnect(this,0,0,0);
    delete ui;
}
void PreMain::InitAreaLimit()
{
    CptDlg dlg;
    dlg.m_task_id = m_task_id;
    dlg.m_step =   m_step;
    dlg.m_pre_ptr = m_pre_ptr;
    dlg.SetAreaLimit();
    SetDDRPicLimit();

}
void PreMain::SetIdAndStep(int id,int step,int x,int y,int edit,QVector<int>vt)
{
    this->m_step = step;
    this->m_task_id = id;

     if(edit != 1)
     {
        AcceleratorModuleInitAll(step);
     }

    m_pre_ptr = GetStepAcceModelPointer(step);
    if(m_pre_ptr == NULL)
        qDebug()<<"GetStepAcceModelPointer(step) = NULL";
    void *edgetPtr = NULL;
    edgetPtr = GetEdgePointAddr();
    ui->labelPic->SetEdgePtr(edgetPtr); //设置边沿提取地址
    int pixel = Get_HWC_Pixel_Size();
    int iVga2Sub = Get_HWC_Vga2Sub_Factor();
    ui->labelPic->SetHWCVga2Sub(iVga2Sub);
    CGetImageThread::Instance()->SetPixel(pixel);
    m_listX = ui->labelPic->x()+x;
    m_listY = ui->labelPic->y()+y;
    InitPreList(edit,vt);


    UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,0xffffffff);
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
    {
        return ;
    }

    if(ptr->execute_flag == 1)
    {
        ui->checkBoxRun->setChecked(true);

    }else
    {
        ui->checkBoxRun->setChecked(false);
    }
    InitAreaLimit();
}
void PreMain::AcceleratorModuleEnable()
{
    StepAcceleratorModuleEnable(m_step);
}
int PreMain::IsAddPreItem(int index)
{
    int ret = 0;
    if(index == ACCE_CPT_MODEL_ID)
    {
        int count = ui->listWidget->count();
        if(count > 0)
        {
            QMessageBox::about(NULL,tr("提示"),tr("图像预处理模块必须加入到第一行"));
            return ret;
        }
        //FindCptTwoLines();
    }
    if(ui->listWidget->count()==0)
    {
        if(index != ACCE_CPT_MODEL_ID)
        {
            QMessageBox::about(NULL,tr("提示"),tr("第一行必须加入图像预处理模块"));
            return ret ;
        }
    }
    if(FindTaskInTable(index)== 1)
    {
        QMessageBox::about(NULL,tr("提示"),tr("加载的预处理模块已在列表中"));
        return ret;
    }
    ret =1;
    return ret;

}
int PreMain::IsPreSel(int index)
{
    int ret =0;
    int row = ui->listWidget->currentRow();
    if(row >=0)
    {
        QListWidgetItem *item =  ui->listWidget->item(ui->listWidget->currentRow());
        QWidget *qWidget = ui->listWidget->itemWidget(item);
        int taskIndex = ((PretreatmentModuleItem*)qWidget)->m_taskKind;
        if(acce_valid_src[index][taskIndex]!=1)
        {
            QMessageBox::about(NULL,tr("提示"),tr("不能添加该模块，图像源不对"));
            return ret;
        }
    }
    if(row >=0)
    {
        int lastRow =row+1;
        if(lastRow < ui->listWidget->count())
        {
            QListWidgetItem *item =  ui->listWidget->item(lastRow);
            QWidget *qWidget = ui->listWidget->itemWidget(item);
            int taskIndex = ((PretreatmentModuleItem*)qWidget)->m_taskKind;
            QString strName = ((PretreatmentModuleItem*)qWidget)->GetInfoName();
            if(acce_valid_src[taskIndex][index]!=1)
            {
                QMessageBox::about(NULL,tr("提示"),tr("不能添加该模块，图像源不对"));
                return ret;
            }
        }
    }
    ret =1;
    return ret;
}
void PreMain::ExchangeItemData(int iRow)
{

    int maxRow = ui->listWidget->count()-1;
    for(int i = maxRow; i > iRow;i--)
    {
        QListWidgetItem *item =  ui->listWidget->item(i);
        QWidget *qWidget = ui->listWidget->itemWidget(item);

        QListWidgetItem *itemPrev =  ui->listWidget->item(i-1);
        QWidget *qWidgetPrev = ui->listWidget->itemWidget(itemPrev);

        QString strNamePrev = ((PretreatmentModuleItem*)qWidgetPrev)->GetInfoName();
        int bChecekPrev =((PretreatmentModuleItem*)qWidgetPrev)->GetCheckedValue();
        int taskIndexPrev = ((PretreatmentModuleItem*)qWidgetPrev)->m_taskKind;

        QString strNameCurrent= ((PretreatmentModuleItem*)qWidget)->GetInfoName();
        int bChecekCurrent =((PretreatmentModuleItem*)qWidget)->GetCheckedValue();
        int taskIndexCurrent = ((PretreatmentModuleItem*)qWidget)->m_taskKind;

        ((PretreatmentModuleItem*)qWidget)->SetInfoName(strNamePrev);
        ((PretreatmentModuleItem*)qWidget)->m_taskKind = taskIndexPrev;
        ((PretreatmentModuleItem*)qWidget)->SetCheckdevalue(bChecekPrev);

        ((PretreatmentModuleItem*)qWidgetPrev)->SetInfoName(strNameCurrent);
        ((PretreatmentModuleItem*)qWidgetPrev)->m_taskKind = taskIndexCurrent;
        ((PretreatmentModuleItem*)qWidgetPrev)->SetCheckdevalue(bChecekCurrent);
    }
}
void PreMain::on_btnAdd_clicked()
{
    PretreatmentSummaryDialog dlg;
    dlg.SetLocation(660,50);
    int ret = dlg.exec();

    if(ret == QDialog::Accepted)
    {
        QString strName = dlg.GetStrName();
        int index = dlg.GetIndex();
        int row = ui->listWidget->currentRow();
        if(IsAddPreItem(index)==0)
            return;
        if(IsPreSel(index) == 0)
            return;
        SetItemEnable(1);
        AddItemData(strName,index,1,ui->listWidget->count());

        if(row >= 0 && ui->listWidget->count()>2 && row+1 != ui->listWidget->count())
        {
            ExchangeItemData(row+1);
            ui->listWidget->setCurrentRow(row+1);
        }

        SetItemCurrentRow();
        InitAccTaskID();
        IniPreSrc();
        InitPaintPoints(index);
        QVector<int>vt_taskid = this->m_vt_points_taskid;
        RemovePointsVt(ACCE_EDGE_EXTRACT_MODLE_ID);
        RemovePointsVt(ACCE_SKE_MATCH_MODLE_ID);
        InitPaintPoints(index);
        ListCurrentRowInfo();
        m_fun_ptr.value(index).Set_model_enable(1,this);
        m_fun_ptr.value(index).List_model_dlg(index,this);
        this->m_vt_points_taskid = vt_taskid;
        if(vt_taskid.count() > 0)
            Start_timer();
        GetImageOutPut();


    }
}
int PreMain::FindTaskInTable(int taskId)
{
    int count = ui->listWidget->count();
    int inTable = 0;
    if(count == 0)
        return 0;
    for (int i = 0; i<count; i++)
    {
        QListWidgetItem *item =  ui->listWidget->item(i);
        QWidget *qWidget = ui->listWidget->itemWidget(item);
        int taskIdTemp = ((PretreatmentModuleItem*)qWidget)->m_taskKind;

        if(taskIdTemp == taskId)
        {
            inTable = 1;
            break;
        }
    }
    return inTable;
}
void PreMain::InitPreList(int iEdit, QVector<int>vt)
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        int count;
        if(iEdit !=1)
        {
            count = vt.count();
            ptr->accelerator_num = count;
        }
        else
        {
            count= ptr->accelerator_num;
        }

        PretreatmentSummaryDialog dlg;

        for(int i=0; i<count;i++)
        {
            int taskId =0;
            if(iEdit !=1)
            {
                taskId = vt[i];
                ptr->accelerator[i] = taskId;
            }
            else
            {
                taskId = ptr->accelerator[i];
            }

            int index =  dlg.GetNameIndexById(taskId);
            QString strName =  dlg.GetStrNameByArrIndex(index);
            AddItemData(strName,taskId,PreModelEnabel(taskId),i);
            m_fun_ptr.value(taskId).Set_model_enable(PreModelEnabel(taskId),this);
            InitPaintPoints(taskId);
        }
        if(iEdit !=1)
        {
            IniPreSrc();
            ModuleConfigAll();
        }
        //GetImageOutPut();
    }
}
int PreMain::PreModelEnabel(int taskId)
{
    int ret = 0;
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr !=NULL)
    {
        switch (taskId) {
        case ACCE_CPT_MODEL_ID:
            ret =ptr->image_acce_param.cpt_model_cfg.model_enable;
            break;
        case ACCE_PRE_MODEL_ID: ///< 图像预处理转换模块
            ret = ptr->image_acce_param.pre_model_cfg.model_enable;;
            break;
        case ACCE_BW_PROC_MODEL_ID:///< 二值化处理模块
            ret = ptr->image_acce_param.bw_proc_model_cfg.model_enable;
            break;
        case ACCE_SKE_MATCH_MODLE_ID:///< 轮廓匹配
            ret = ptr->image_acce_param.match_model_cfg.model_enable;
            break;
        case ACCE_EDGE_EXTRACT_MODLE_ID:///< 边沿提取
            ret = ptr->image_acce_param.side_sel_model_cfg.model_enable;
            break;
        case ACCE_SIDE_CHOOSE_MODEL_ID:///< 边沿筛选
            ret = ptr->image_acce_param.side_choose_model_cfg.side_choose_angle_en;
            break;
        case ACCE_CURVE_FITTING_MODLE_ID:///< 曲线拟合
            ret = ptr->image_acce_param.curve_fit_model_cfg.model_enable;
            break;
        case ACCE_CONNECT_REGION_MODLE_ID:///< 连通域
            ret = ptr->image_acce_param.link_model_cfg.model_enable;
            break;
        case ACCE_COLOR_EXTRACT_MODLE_ID:///< 色彩提取
            ret = ptr->image_acce_param.color_draw_model_cfg.model_enable;
            break;
        case ACCE_AREA_SELECT_MODEL_ID: ///< 区域筛选
            ret = ptr->image_acce_param.select_model_cfg.model_enable;
            break;
        case ACCE_HIST_MODEL_ID: ///< 直方图统计
            ret = ptr->image_acce_param.hist_model_cfg.model_enable;
            break;
        default:
            break;
        }
    }
    return ret;
}
void PreMain::AddItemData(QString strName,int index,int bCheck,int current)
{
    PretreatmentModuleItem *p_PretreatmentModuleItem = new PretreatmentModuleItem;
    p_PretreatmentModuleItem->setAttribute(Qt::WA_DeleteOnClose);
    p_PretreatmentModuleItem->SetInfoName(strName);
    p_PretreatmentModuleItem->m_taskKind = index;
    p_PretreatmentModuleItem->m_current_row = current;
    p_PretreatmentModuleItem->SetCheckdevalue(bCheck);
    int size =ui->listWidget->count();
    QListWidgetItem* mItem = new QListWidgetItem(ui->listWidget);
    ui->listWidget->setItemWidget(mItem,(QWidget*)p_PretreatmentModuleItem);
    ui->listWidget->item(size)->setSizeHint(QSize(340,50));
    ui->listWidget->setCurrentRow(size);
    connect(p_PretreatmentModuleItem,&PretreatmentModuleItem::SignalOperate,this,&PreMain::OperateSlots);
}
void PreMain::OperateSlots(int iOperate,int itaskKind,int value,int current)
{
    //QVector<int>vt_taskid;
    ui->listWidget->setCurrentRow(current);
    switch (iOperate) {
    case PREENABLE:
        m_fun_ptr.value(itaskKind).Set_model_enable(value,this);
        switch (value) {
        case 1:
            InitPaintPoints(itaskKind);
            break;
        case 0:
            RemovePointsVt(itaskKind);
            break;
        default:
            break;
        }
        CheckBoxControItemEnable(value);
        IniPreSrc();
        break;
    case PREDETAIL:
        //vt_taskid = this->m_vt_points_taskid;
        RemovePointsVt(ACCE_EDGE_EXTRACT_MODLE_ID);
        RemovePointsVt(ACCE_SKE_MATCH_MODLE_ID);
        InitPaintPoints(itaskKind);
        m_fun_ptr.value(itaskKind).List_model_dlg(itaskKind,this);
        RemovePointsVt(itaskKind);
        PaintPicPoint();
        break;
    default:
        break;
    }

    GetImageOutPut();
    ListInfo(GetStrInfor(itaskKind));
}
void PreMain::PaintPicPoint()
{
    int count = ui->listWidget->count();
    for(int i = 0; i<count;i++)
    {
        QListWidgetItem *item =  ui->listWidget->item(count-i-1);
        QWidget *qWidget = ui->listWidget->itemWidget(item);
        int taskIndex= ((PretreatmentModuleItem*)qWidget)->m_taskKind;
        InitPaintPoints(taskIndex);
    }

}
void PreMain::InitAccTaskID()
{
    //memset(m_buf,0,sizeof(m_buf));
    int count = ui->listWidget->count();
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;

    if(ptr != NULL)
    {
        ptr->accelerator_num = count;
        memset( ptr->accelerator,0,sizeof(ptr->accelerator));
    }

    for (int i = 0; i<count; i++)
    {
        QListWidgetItem *item =  ui->listWidget->item(i);
        QWidget *qWidget = ui->listWidget->itemWidget(item);

        if(ptr != NULL)
        {
            ptr->accelerator[i] = ((PretreatmentModuleItem*)qWidget)->m_taskKind;
        }
    }
    AcceleratorModuleConfigAll(m_step);
}

void PreMain::InitFunPtr()
{
    STRUCT_FUN_PTR cptMode;
    cptMode.List_model_dlg=ListCptDlg;
    cptMode.Set_ddr_enable=SetCptDDREnable;
    cptMode.Set_model_enable = SetCptEnable;
    m_fun_ptr.insert(ACCE_CPT_MODEL_ID,cptMode);

    STRUCT_FUN_PTR preMode;
    preMode.List_model_dlg=ListPreDlg;
    preMode.Set_ddr_enable=SetPreDDREnable;
    preMode.Set_model_enable = SetPreEnable;
    preMode.SetPicSrc = SetPreSrcValue;
    m_fun_ptr.insert(ACCE_PRE_MODEL_ID,preMode);

    STRUCT_FUN_PTR bwMode;
    bwMode.List_model_dlg=ListBWProcDlg;
    bwMode.Set_ddr_enable=SetBWProcDDREnable;
    bwMode.Set_model_enable =SetBWProcEnable;
    bwMode.SetPicSrc = SetBWSrcValue;
    m_fun_ptr.insert(ACCE_BW_PROC_MODEL_ID,bwMode);

    STRUCT_FUN_PTR skeMatchMode;
    skeMatchMode.List_model_dlg=ListSkeMatchProcDlg;
    skeMatchMode.Set_ddr_enable=SetSkeMatchProcDDREnable;
    skeMatchMode.Set_model_enable =SetSkeMatchProcEnable;
    skeMatchMode.SetPicSrc = SetSkeMatchProcSrcValue;
    m_fun_ptr.insert(ACCE_SKE_MATCH_MODLE_ID,skeMatchMode);

    STRUCT_FUN_PTR edgeMode;
    edgeMode.List_model_dlg=ListEdgeExtractDlg;
    edgeMode.Set_ddr_enable=SetEdgeExtractDDREnable;
    edgeMode.Set_model_enable =SetEdgeExtractEnable;
    edgeMode.SetPicSrc = SetEdgeExtractSrcValue;
    m_fun_ptr.insert(ACCE_EDGE_EXTRACT_MODLE_ID,edgeMode);

    STRUCT_FUN_PTR connectMode;
    connectMode.List_model_dlg=ListConnectDlg;
    connectMode.Set_ddr_enable=SetConnectDDREnable;
    connectMode.Set_model_enable =SetConnectEnable;
    connectMode.SetPicSrc = SetConnectSrcValue;
    m_fun_ptr.insert(ACCE_CONNECT_REGION_MODLE_ID,connectMode);

    STRUCT_FUN_PTR colorMode;
    colorMode.List_model_dlg=ListColorExtractDlg;
    colorMode.Set_ddr_enable=SetColorExtractDDREnable;
    colorMode.Set_model_enable =SetColorExtractEnable;
    colorMode.SetPicSrc = SetColorExtractSrcValue;
    m_fun_ptr.insert(ACCE_COLOR_EXTRACT_MODLE_ID,colorMode);

    STRUCT_FUN_PTR areaSelectMode;
    areaSelectMode.List_model_dlg=ListAreaSelectDlg;
    areaSelectMode.Set_ddr_enable=SetAreaSelectDDREnable;
    areaSelectMode.Set_model_enable =SetAreaSelectEnable;
    areaSelectMode.SetPicSrc = SetAreaSelectSrcValue;
    m_fun_ptr.insert(ACCE_AREA_SELECT_MODEL_ID,areaSelectMode);

    STRUCT_FUN_PTR grayHistogramMode;
    grayHistogramMode.List_model_dlg = ListGrayHistogramDlg;
    grayHistogramMode.Set_ddr_enable = SetGrayHistogramDDREnable;
    grayHistogramMode.Set_model_enable = SetGrayHistogramEnable;
    grayHistogramMode.SetPicSrc = SetGrayHistogramSrcValue;
    m_fun_ptr.insert(ACCE_HIST_MODEL_ID,grayHistogramMode);


}
void PreMain::SetItemCurrentRow()
{
    int count = ui->listWidget->count();
    for(int i = 0; i < count; i++)
    {
        QWidget *pWidget = ui->listWidget->itemWidget(ui->listWidget->item(i));
        ((PretreatmentModuleItem*)pWidget)->m_current_row = i;
    }
}
void PreMain::ListCptVga()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
    {
        return ;
    }
    ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_CPT_MODEL_ID;
    AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
    UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,0xffffffff);
}
int PreMain::GetImageOutPut()
{
    AcceModuleSrcSelAutoSet(this->m_step);
    UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,0xffffffff);

    return 0;
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
    {
        return 0;
    }
    int count = ui->listWidget->count();

    for(int i = 0; i<count;i++)
    {
        QListWidgetItem *item =  ui->listWidget->item(count-i-1);
        QWidget *qWidget = ui->listWidget->itemWidget(item);
        QString strName= ((PretreatmentModuleItem*)qWidget)->GetInfoName();
        int bChecek =((PretreatmentModuleItem*)qWidget)->GetCheckedValue();
        int taskIndex= ((PretreatmentModuleItem*)qWidget)->m_taskKind;

        if(taskIndex == ACCE_CONNECT_REGION_MODLE_ID)
        {
            continue;
        }
        else if(taskIndex == ACCE_SKE_MATCH_MODLE_ID)
        {
            continue;
        }else if(taskIndex == ACCE_HIST_MODEL_ID)
        {
            continue;
        }
        else if(taskIndex == ACCE_EDGE_EXTRACT_MODLE_ID)
        {
            if(ptr->image_acce_param.side_sel_model_cfg.side_mode_sel == 0)
            {
                continue;
            }
        }
        if(bChecek == 1)
        {
            m_image_out_src = taskIndex;
            //ptr->image_acce_param.pre_model_cfg.pre_wr_ddr_en =1;
            // ptr->image_acce_param.pre_model_cfg.pre_src_sel = m_image_out_src;
            ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = m_image_out_src;
            //AcceleratorModuleConfig(m_image_out_src,m_step);
            AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);

            UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,0xffffffff);
            break;
        }
    }
    if(count == 0)
    {
        ptr->image_acce_param.vga_model_cfg.vga_pic_src_sel = ACCE_CPT_MODEL_ID;
        AcceleratorModuleConfig(ACCE_VGA_MODEL_ID,m_step);
        UtilitiesFun::Instance()->ListVGA(m_listX,m_listY,0xffffffff);
    }
    return m_image_out_src;
}

void PreMain::on_btnDell_clicked()
{
    int iIndex = ui->listWidget->currentRow();
    int taskIdSelect = 0;
    int flag = 0;
    if(iIndex >=0)
    {
        QWidget *qWidgetCpt = ui->listWidget->itemWidget(ui->listWidget->item(iIndex));
        taskIdSelect = ((PretreatmentModuleItem*)qWidgetCpt)->m_taskKind;
        if(((PretreatmentModuleItem*)qWidgetCpt)->m_taskKind==ACCE_CPT_MODEL_ID)
        {
            QMessageBox::information(NULL,tr("提示"),tr("图像预处理模块不能删除"));
            return;
        }
        if(iIndex > 0 && iIndex+1 < ui->listWidget->count())
        {
            QListWidgetItem *itempre =  ui->listWidget->item(iIndex-1);
            QWidget *qWidgetpre = ui->listWidget->itemWidget(itempre);
            int taskIndexpre = ((PretreatmentModuleItem*)qWidgetpre)->m_taskKind;

            QListWidgetItem *itemNext =  ui->listWidget->item(iIndex+1);
            QWidget *qWidgetNext = ui->listWidget->itemWidget(itemNext);
            int taskIndexNext = ((PretreatmentModuleItem*)qWidgetNext)->m_taskKind;

            if(acce_valid_src[taskIndexNext][taskIndexpre] == 1)
            {
                flag = 0;
            }else
            {
                flag =1;
            }
        }
        QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"), tr("确定要删除,将会导致后面加速器模块不能使用?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
        if(rb == QMessageBox::Yes)
        {
            RemovePointsVt(taskIdSelect);
            QListWidgetItem *itemdel= ui->listWidget->takeItem(iIndex);
            delete itemdel;
            if(flag == 1)
            {
                SetItemEnable(0);
            }
            m_fun_ptr.value(taskIdSelect).Set_model_enable(0,this);
            InitAccTaskID();
            IniPreSrc();
            GetImageOutPut();
            ListCurrentRowInfo();
        }
    }
}
void PreMain::IniPreSrc()
{
    AcceModuleSrcSelAutoSet(this->m_step);
    return;
    int count = ui->listWidget->count();
    int taskIdPre = 0;
    int taskIdNow = 0;
    QListWidgetItem *item = NULL;
    QWidget *qWidget = NULL;;
    if(count >0)
    {
        item=  ui->listWidget->item(0);
        qWidget= ui->listWidget->itemWidget(item);
        taskIdPre= ((PretreatmentModuleItem*)qWidget)->m_taskKind;
    }

    for(int i=1;i<count;i++)
    {
        item =  ui->listWidget->item(i);
        qWidget = ui->listWidget->itemWidget(item);
        taskIdNow= ((PretreatmentModuleItem*)qWidget)->m_taskKind;

        /*if(taskIdNow == ACCE_SKE_MATCH_MODLE_ID)
        {
            continue;
        }
        else if(taskIdNow == ACCE_HIST_MODEL_ID)
        {
            continue;
        }
        else if(taskIdNow == ACCE_EDGE_EXTRACT_MODLE_ID)
        {
            ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
            if(ptr != NULL)
            {
                if(ptr->image_acce_param.side_sel_model_cfg.side_mode_sel == 0)
                {
                    continue;
                }
            }
        }*/
        if(((PretreatmentModuleItem*)qWidget)->GetCheckedValue()==1)
        {

            m_fun_ptr.value(taskIdNow).SetPicSrc(taskIdPre,this);
            taskIdPre = taskIdNow;
        }
    }

}
void PreMain::CheckBoxControItemEnable(int value)
{
    int iIndex = ui->listWidget->currentRow();
    if(iIndex>0 &&iIndex<ui->listWidget->count()-1 )
    {
        QListWidgetItem *itempre =  ui->listWidget->item(iIndex-1);
        QWidget *qWidgetpre = ui->listWidget->itemWidget(itempre);
        int taskIndexpre = ((PretreatmentModuleItem*)qWidgetpre)->m_taskKind;

        QListWidgetItem *itemNext =  ui->listWidget->item(iIndex+1);
        QWidget *qWidgetNext = ui->listWidget->itemWidget(itemNext);
        int taskIndexNext = ((PretreatmentModuleItem*)qWidgetNext)->m_taskKind;

        int flag;
        if(acce_valid_src[taskIndexNext][taskIndexpre] == 1)
        {
            flag = 0;
        }else
        {
            flag =1;
        }
        if(value == 0)
        {
            if(flag == 1)
                SetItemEnable(2);
        }else
            SetItemEnable(1);
    }
}
void PreMain::SetItemEnable(int flag)
{
    int row = ui->listWidget->currentRow();

    if(flag>=1)
        row=row+1;

    for(int i = row; i<ui->listWidget->count();i++)
    {
        QListWidgetItem *item =  ui->listWidget->item(i);
        QWidget *qWidget = ui->listWidget->itemWidget(item);
        int taskIndex = ((PretreatmentModuleItem*)qWidget)->m_taskKind;
        int iEnable = ((PretreatmentModuleItem*)qWidget)->GetCheckBoxEnable();

        if(flag ==1)
        {
            if(iEnable ==0)
            {
                ((PretreatmentModuleItem*)qWidget)->SetControlEnable(1);
                m_fun_ptr.value(taskIndex).Set_model_enable(1,this);
            }
        }else
        {
            ((PretreatmentModuleItem*)qWidget)->SetControlEnable(0);
            m_fun_ptr.value(taskIndex).Set_model_enable(0,this);
        }
    }
}
void PreMain::Time_Out()
{
    PointChangeSignal(this->m_vt_points_taskid);
}
void PreMain::Start_timer(int time)
{
    if(!this->m_timer->isActive())
    {
        m_timer->start(time);
    }
}
void PreMain::Stop_timer()
{
    if(this->m_timer->isActive())
        m_timer->stop();
}
void PreMain::InitPaintPoints(int taskid)
{

    if(taskid == ACCE_EDGE_EXTRACT_MODLE_ID || taskid == ACCE_SKE_MATCH_MODLE_ID)
    {
        if(taskid == ACCE_EDGE_EXTRACT_MODLE_ID)
        {
            ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
            if(ptr != NULL)
            {
                if(ptr->image_acce_param.side_sel_model_cfg.side_mode_sel == 1)
                {
                    return;
                }
            }
        }

        if(m_vt_points_taskid.count() == 0)
        {
            this->m_vt_points_taskid.append(taskid);
        }
        else
        {
            int bflag = 1;
            for(int i =0; i<this->m_vt_points_taskid.count();i++)
            {
                if(taskid == m_vt_points_taskid[i])
                {
                    bflag = 0;
                    break;
                }
            }
            if(bflag == 1)
            {
                this->m_vt_points_taskid.append(taskid);
            }
        }
        Start_timer();
    }
}
void PreMain::RemovePointsVt(int taskid)
{
    int count = this->m_vt_points_taskid.count();
    for(int i = 0; i<count;i++)
    {
        if(taskid == m_vt_points_taskid[i])
        {
            this->m_vt_points_taskid.takeAt(i);
        }
    }

    count = this->m_vt_points_taskid.count();

    if(count <=0)
    {
        Stop_timer();
    }
    PointChangeSignal(m_vt_points_taskid);

}
void PreMain::SwitchListEdgePointsSlot(int value)
{
    if(value == 1)
    {
        InitPaintPoints(ACCE_EDGE_EXTRACT_MODLE_ID);
    }else
    {
        RemovePointsVt(ACCE_EDGE_EXTRACT_MODLE_ID);
    }
}
void PreMain::ConnectEdgePointSlot(void *dlg)
{
    EdgeExtractDlg *edgeDlg = (EdgeExtractDlg*)dlg;
    connect(edgeDlg,&EdgeExtractDlg::SignalSwitchListPoint,this,&PreMain::SwitchListEdgePointsSlot);
}
void PreMain::DisConnectEdgePointSlot(void *dlg)
{
    EdgeExtractDlg *edgeDlg = (EdgeExtractDlg*)dlg;
    disconnect(edgeDlg,&EdgeExtractDlg::SignalSwitchListPoint,this,&PreMain::SwitchListEdgePointsSlot);
}
void PreMain::on_btnClear_clicked()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(NULL, tr("提示"),tr("确定要清空预处理模块列表"), QMessageBox::Yes | QMessageBox::No,  QMessageBox::No);

    if(rb == QMessageBox::Yes)
    {
        int count = ui->listWidget->count();

        for(int i = 0; i< count;i++)
        {
            int row = ui->listWidget->count() -1;
            QListWidgetItem *item =  ui->listWidget->item(row);
            QWidget *qWidget = ui->listWidget->itemWidget(item);
            int taskIdSelect = ((PretreatmentModuleItem*)qWidget)->m_taskKind;
            QListWidgetItem *itemdel= ui->listWidget->takeItem(row);
            delete itemdel;
            m_fun_ptr.value(taskIdSelect).Set_model_enable(0,this);
        }

        InitAccTaskID();
        GetImageOutPut();
        UtilitiesFun::Instance()->SetStartX(0);
        UtilitiesFun::Instance()->SetEndX(640);
        UtilitiesFun::Instance()->SetStartY(UtilitiesFun::Instance()->GetCmosStartY());
        UtilitiesFun::Instance()->SetEndY(UtilitiesFun::Instance()->GetCmosEndY());
        UtilitiesFun::Instance()->SetCptType(CPT_DDR_PIC);
        ListInfo("图像加速器模块设定适用于图像处理的预处理种类，指定了复数个种类，以从上往方下的方式进行处理");
    }
}
void PreMain::ModuleConfigAll()
{

    AcceleratorModuleConfigAll(m_step);
}
void PreMain::PreAllModuleDisable()
{

   AcceleratorAllModuleClose();
}
void PreMain::SetDDRPicLimit()
{
    ui->labelPic->Set_startX(UtilitiesFun::Instance()->GetStartX());
    ui->labelPic->Set_endX(UtilitiesFun::Instance()->GetEndX());
    ui->labelPic->Set_startY(UtilitiesFun::Instance()->GetStartY());
    ui->labelPic->Set_endY(UtilitiesFun::Instance()->GetEndY());
    ui->labelPic->update();
}
void PreMain::SetTaskListName(QVector<QString>vtName)
{
    int count = vtName.count();
    int index = m_step -1;

    for(int i=0; i<count;i++)
    {
        if(i<index)
        {
            ui->comboBoxTaskList->addItem(vtName[i]);
        }
    }
}

void PreMain::on_checkBoxRun_clicked()
{
    ACCE_MODEL *ptr = (ACCE_MODEL*)m_pre_ptr;
    if(ptr == NULL)
    {
        return ;
    }
    if(ui->checkBoxRun->isChecked())
    {
        ptr->execute_flag = 1;

    }else
    {
        ptr->execute_flag = 0;
    }

}

void PreMain::on_btnCopy_clicked()
{
    on_btnClear_clicked();
    if(ui->listWidget->count() > 0)
        return;
    QString strTaskName = ui->comboBoxTaskList->currentText();
    int index = strTaskName.indexOf('.');
    QString strStep = strTaskName.left(index);
    int iStep = strStep.toInt();
    AcceleratorModuleParamsCopy(iStep,m_step);
    QVector<int>vt;
    InitPreList(1, vt);
    GetImageOutPut();
    ListInfo("图像加速器模块设定适用于图像处理的预处理种类，指定了复数个种类，以从上往方下的方式进行处理");
}
void PreMain::ListInfo(QString strInfo)
{

    ui->txtInfo->clear();
    ui->txtInfo->append(strInfo);

}
QString PreMain::GetStrInfor(int taskId)
{
    QString strRet = "";

    switch (taskId) {
    case ACCE_CPT_MODEL_ID: //cpt
        strRet = "图像源为摄像头实时采集或来源内存图片数据";
        break;
    case ACCE_PRE_MODEL_ID: //图像预处理转换
        strRet = "图像预处理主要是消除图像中无关的信息,恢复有用的真实信息,增强有关信息的可检测性和最大限度地简化数据,从而改进特征抽取、图像分割、匹配和识别的可靠性";
        break;
    case ACCE_BW_PROC_MODEL_ID: //二值化处理
        strRet = "二值化就是将图像上的像素点的灰度值设置为0或255，这样将使整个图像呈现出明显的黑白效果";
        break;
    case ACCE_SKE_MATCH_MODLE_ID: //轮廓匹配
        strRet = "轮廓匹配模块";
        break;
    case ACCE_EDGE_EXTRACT_MODLE_ID: //边沿提取
        strRet = "利用边缘增强算子，突出图像中的局部边缘，然后定义象素的“边缘强度”，通过设置阈值的方法提取边缘点集";
        break;
    case ACCE_CONNECT_REGION_MODLE_ID: //连通域
        strRet = "图像连通域的标记";
        break;
    case ACCE_COLOR_EXTRACT_MODLE_ID: //色彩提取
        strRet = "通过任意的抽取方法，抽取指定颜色";
        break;
    case ACCE_AREA_SELECT_MODEL_ID://区域筛选
        strRet = "根据选择的区域提取点或提取图像";
        break;
    case ACCE_HIST_MODEL_ID: //直方图统计
        strRet = "直方图是图像中像素强度分布的图形表达方式，它统计了每一个强度值所具有的像素个数";
        break;
    default:
        break;
    }
    return strRet;
}

void PreMain::on_listWidget_clicked(const QModelIndex &index)
{
    int row = index.row();

    if(row>=0)
    {
        QListWidgetItem *item =  ui->listWidget->item(row);
        QWidget *qWidget = ui->listWidget->itemWidget(item);
        int itaskKind= ((PretreatmentModuleItem*)qWidget)->m_taskKind;
        ListInfo(GetStrInfor(itaskKind));
    }
}
void PreMain::ListCurrentRowInfo()
{
    int row = ui->listWidget->currentRow();
    if(row >=0)
    {
        QListWidgetItem *item =  ui->listWidget->item(row);
        QWidget *qWidget = ui->listWidget->itemWidget(item);
        int itaskKind= ((PretreatmentModuleItem*)qWidget)->m_taskKind;
        ListInfo(GetStrInfor(itaskKind));
    }
}
void PreMain::SetColor(void *pen_color)
{
    m_pen_color = pen_color;
    ui->labelPic->SetPenColor(pen_color);
}
