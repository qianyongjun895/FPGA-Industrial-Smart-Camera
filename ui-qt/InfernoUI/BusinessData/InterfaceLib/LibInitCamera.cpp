#include "LibInitCamera.h"
#include <QLibrary>
#include <QMessageBox>
#include "lzynq_include/Hardware_Init.h"
#include "lzynq_include/cmos_common.h"


LibInitCamera::LibInitCamera()
{

}
int LibInitCamera::IniCamera()
{
   typedef int (*Fun_IniCamera)(); //定义函数指针，以备调用
   int result=0;
   //if(Hardware_Init(2, 60, 0x00323232) !=0)
   result = Hardware_Init(2, 60, 0x00323232);
   /*if(result !=0)
   {
       QMessageBox::information(NULL,"提示","初始化硬件失败!");
   }*/
   return result;

}
  /* 曝光 */
void LibInitCamera::Set_Exposure(int value)
{
    Set_HWC_CMOS_Exposure(value);
}
/* 增益 */
void LibInitCamera::Set_Gain(int value)
{
    Set_HWC_CMOS_Gain(value);
}
//调用相机图像Y方向裁剪函数
 int LibInitCamera::Set_CMOS_Capture_Y_Clip(unsigned int start_y, unsigned int height)
 {
    return Set_HWC_CMOS_Capture_Y_Clip(start_y,height);
 }
//获取曝光初始值
 unsigned int LibInitCamera::Get_Exposure_Init()
 {
     return Get_HWC_Exposure_Init();
 }
//获取曝光最大值
 unsigned int LibInitCamera::Get_Exposure_Max()
 {
     return Get_HWC_Exposure_Max();
 }
//获取exposure_min
 unsigned int LibInitCamera::Get_Exposure_Min()
 {
    return Get_HWC_Exposure_Min();
 }

