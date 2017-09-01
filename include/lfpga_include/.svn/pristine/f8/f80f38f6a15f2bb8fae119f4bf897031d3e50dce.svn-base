#ifndef AREASELECT_H
#define AREASELECT_H

#include "define.h"
#include "AcceCommon.h"



/** Model(P42)区域选择 */
#define REGION_SEL_CTRL_REG     0x190                   ///<  区域选择寄存器
#define REGION_SEL_CTRL_EN_MASK	0x1                     ///<  区域选择使能掩码
#define REGION_SEL_CTRL_EN_OFFSET   0
#define REGION_SEL_CTRL_MONO_WR_DDR_EN_MASK	    0x10    ///<  区域选择黑色图像写入DDR使能掩码
#define REGION_SEL_CTRL_MONO_WR_DDR_EN_OFFSET	4
#define REGION_SEL_CTRL_COLOR_WR_DDR_EN_MASK	0x20    ///<  区域选择彩色图像写入DDR使能掩码
#define REGION_SEL_CTRL_COLOR_WR_DDR_EN_OFFSET  5
#define REGION_SEL_CTRL_SRC_SEL_MASK            0x3f00  ///<  区域选择输入选择
#define REGION_SEL_CTRL_SRC_SEL_OFFSET          8

#define REGION_SEL_CTRL_WR_ADDR_REG         0x1d0       ///<  区域选择写入DDR地址寄存器
#define REGION_SEL_CTRL_RGB_BACK_REG        0x1d2       ///<  区域选择背景颜色

#define REGION_SEL_CTRL_OFFSET_REG          0x191       ///<  区域选择坐标偏移寄存器
#define REGION_SEL_CTRL_OFFSET_X_MASK       0xffff      ///<  区域选择坐标偏移x坐标掩码
#define REGION_SEL_CTRL_OFFSET_X_OFFSET     0
#define REGION_SEL_CTRL_OFFSET_Y_MASK       0xffff0000  ///<  区域选择坐标偏移y坐标掩码
#define REGION_SEL_CTRL_OFFSET_Y_OFFSET     16

#define REGION_SEL_CTRL_POLYGON_EN_REG      0x192       ///<  八边形顶点使能寄存器
#define REGION_SEL_CTRL_POLYGON0_EN_MASK    0xff        ///<  第一个八边形顶点使能掩码
#define REGION_SEL_CTRL_POLYGON0_EN_OFFSET  0
#define REGION_SEL_CTRL_POLYGON1_EN_MASK    0xff00      ///<  第二个八边形顶点使能掩码
#define REGION_SEL_CTRL_POLYGON1_EN_OFFSET  8
#define REGION_SEL_CTRL_POLYGON2_EN_MASK    0xff0000    ///<  第三个八边形顶点使能掩码
#define REGION_SEL_CTRL_POLYGON2_EN_OFFSET  16
#define REGION_SEL_CTRL_POLYGON3_EN_MASK    0xff000000  ///<  第四个八边形顶点使能掩码
#define REGION_SEL_CTRL_POLYGON3_EN_OFFSET  24

#define REGION_SEL_CTRL_POLYGON_REG         0x193       ///<  图形内外取反使能与相互逻辑关系寄存器
//#define REGION_SEL_CTRL_POLYGON_INV_MASK  0xf         ///<  四个多边形内外取反使能掩码
#define REGION_SEL_CTRL_POLYGON0_INV_MASK   0x1         ///<  多边形1内外取反使能掩码
#define REGION_SEL_CTRL_POLYGON0_INV_OFFSET 0
#define REGION_SEL_CTRL_POLYGON1_INV_MASK   0x2         ///<  多边形2内外取反使能掩码
#define REGION_SEL_CTRL_POLYGON1_INV_OFFSET 1
#define REGION_SEL_CTRL_POLYGON2_INV_MASK   0x4         ///<  多边形3内外取反使能掩码
#define REGION_SEL_CTRL_POLYGON2_INV_OFFSET 2
#define REGION_SEL_CTRL_POLYGON3_INV_MASK   0x8         ///<  多边形4内外取反使能掩码
#define REGION_SEL_CTRL_POLYGON3_INV_OFFSET 3
//#define REGION_SEL_CTRL_POLYGON_AND_MASK  0xf0        ///<  四个多边形逻辑关系掩码，1=AND使能； 0=or
//#define REGION_SEL_CTRL_RING_EN_MASK      0xf000      ///<  四个环形使能掩码
#define REGION_SEL_CTRL_RING0_EN_MASK       0x1000      ///<  环形1使能掩码
#define REGION_SEL_CTRL_RING0_EN_OFFSET     12
#define REGION_SEL_CTRL_RING1_EN_MASK       0x2000      ///<  环形2使能掩码
#define REGION_SEL_CTRL_RING1_EN_OFFSET     13
#define REGION_SEL_CTRL_RING2_EN_MASK       0x4000      ///<  环形3使能掩码
#define REGION_SEL_CTRL_RING2_EN_OFFSET     14
#define REGION_SEL_CTRL_RING3_EN_MASK       0x8000      ///<  环形4使能掩码
#define REGION_SEL_CTRL_RING3_EN_OFFSET     15
//#define REGION_SEL_CTRL_RING_INV_MASK     0xf0000     ///<  四个环形，内外取反使能掩码
#define REGION_SEL_CTRL_RING0_INV_MASK      0x10000     ///<  环形1，内外取反使能掩码
#define REGION_SEL_CTRL_RING0_INV_OFFSET    16
#define REGION_SEL_CTRL_RING1_INV_MASK      0x20000     ///<  环形2，内外取反使能掩码
#define REGION_SEL_CTRL_RING1_INV_OFFSET    17
#define REGION_SEL_CTRL_RING2_INV_MASK      0x40000     ///<  环形3，内外取反使能掩码
#define REGION_SEL_CTRL_RING2_INV_OFFSET    18
#define REGION_SEL_CTRL_RING3_INV_MASK      0x80000     ///<  环形4，内外取反使能掩码
#define REGION_SEL_CTRL_RING3_INV_OFFSET    19
//#define REGION_SEL_CTRL_RING_AND_MASK     0xf00000    ///<  四个环形逻辑关系掩码，1=AND使能； 0=or

#define REGION_SEL_CTRL_RECT_A0_REG         0x194       ///<  第一个八边形，a顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_A0_X_MASK      0xffff      ///<  第一个八边形，a顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_A0_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_A0_Y_MASK      0xffff0000  ///<  第一个八边形，a顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_A0_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_B0_REG         0x195       ///<  第一个八边形，b顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_B0_X_MASK      0xffff      ///<  第一个八边形，b顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_B0_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_B0_Y_MASK      0xffff0000  ///<  第一个八边形，b顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_B0_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_C0_REG         0x196       ///<  第一个八边形，c顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_C0_X_MASK      0xffff      ///<  第一个八边形，c顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_C0_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_C0_Y_MASK      0xffff0000  ///<  第一个八边形，c顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_C0_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_D0_REG         0x197       ///<  第一个八边形，d顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_D0_X_MASK      0xffff      ///<  第一个八边形，d顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_D0_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_D0_Y_MASK      0xffff0000  ///<  第一个八边形，d顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_D0_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_E0_REG         0x198       ///<  第一个八边形，e顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_E0_X_MASK      0xffff      ///<  第一个八边形，e顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_E0_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_E0_Y_MASK      0xffff0000  ///<  第一个八边形，e顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_E0_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_F0_REG         0x199       ///<  第一个八边形，f顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_F0_X_MASK      0xffff      ///<  第一个八边形，f顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_F0_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_F0_Y_MASK      0xffff0000  ///<  第一个八边形，f顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_F0_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_G0_REG         0x19a       ///<  第一个八边形，g顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_G0_X_MASK      0xffff      ///<  第一个八边形，g顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_G0_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_G0_Y_MASK      0xffff0000  ///<  第一个八边形，g顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_G0_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_H0_REG         0x19b       ///<  第一个八边形，h顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_H0_X_MASK      0xffff      ///<  第一个八边形，h顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_H0_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_H0_Y_MASK      0xffff0000  ///<  第一个八边形，h顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_H0_Y_OFFSET    16

#define REGION_SEL_CTRL_RECT_A1_REG         0x19c       ///<  第二个八边形，a顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_A1_X_MASK      0xffff      ///<  第二个八边形，a顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_A1_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_A1_Y_MASK      0xffff0000  ///<  第二个八边形，a顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_A1_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_B1_REG         0x19d       ///<  第二个八边形，b顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_B1_X_MASK      0xffff      ///<  第二个八边形，b顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_B1_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_B1_Y_MASK      0xffff0000  ///<  第二个八边形，b顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_B1_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_C1_REG         0x19e       ///<  第二个八边形，c顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_C1_X_MASK      0xffff      ///<  第二个八边形，c顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_C1_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_C1_Y_MASK      0xffff0000  ///<  第二个八边形，c顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_C1_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_D1_REG         0x19f       ///<  第二个八边形，d顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_D1_X_MASK      0xffff      ///<  第二个八边形，d顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_D1_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_D1_Y_MASK      0xffff0000  ///<  第二个八边形，d顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_D1_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_E1_REG         0x1a0       ///<  第二个八边形，e顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_E1_X_MASK      0xffff      ///<  第二个八边形，e顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_E1_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_E1_Y_MASK      0xffff0000  ///<  第二个八边形，e顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_E1_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_F1_REG         0x1a1       ///<  第二个八边形，f顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_F1_X_MASK      0xffff      ///<  第二个八边形，f顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_F1_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_F1_Y_MASK      0xffff0000  ///<  第二个八边形，f顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_F1_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_G1_REG         0x1a2       ///<  第二个八边形，g顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_G1_X_MASK      0xffff      ///<  第二个八边形，g顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_G1_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_G1_Y_MASK      0xffff0000  ///<  第二个八边形，g顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_G1_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_H1_REG         0x1a3       ///<  第二个八边形，h顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_H1_X_MASK      0xffff      ///<  第二个八边形，h顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_H1_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_H1_Y_MASK      0xffff0000  ///<  第二个八边形，h顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_H1_Y_OFFSET    16

#define REGION_SEL_CTRL_RECT_A2_REG         0x1a4       ///<  第三个八边形，a顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_A2_X_MASK      0xffff      ///<  第三个八边形，a顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_A2_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_A2_Y_MASK      0xffff0000  ///<  第三个八边形，a顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_A2_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_B2_REG         0x1a5       ///<  第三个八边形，b顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_B2_X_MASK      0xffff      ///<  第三个八边形，b顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_B2_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_B2_Y_MASK      0xffff0000  ///<  第三个八边形，b顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_B2_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_C2_REG         0x1a6       ///<  第三个八边形，c顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_C2_X_MASK      0xffff      ///<  第三个八边形，c顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_C2_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_C2_Y_MASK      0xffff0000  ///<  第三个八边形，c顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_C2_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_D2_REG         0x1a7       ///<  第三个八边形，d顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_D2_X_MASK      0xffff      ///<  第三个八边形，d顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_D2_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_D2_Y_MASK      0xffff0000  ///<  第三个八边形，d顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_D2_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_E2_REG         0x1a8       ///<  第三个八边形，e顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_E2_X_MASK      0xffff      ///<  第三个八边形，e顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_E2_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_E2_Y_MASK      0xffff0000  ///<  第三个八边形，e顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_E2_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_F2_REG         0x1a9       ///<  第三个八边形，f顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_F2_X_MASK      0xffff      ///<  第三个八边形，f顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_F2_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_F2_Y_MASK      0xffff0000  ///<  第三个八边形，f顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_F2_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_G2_REG         0x1aa       ///<  第三个八边形，g顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_G2_X_MASK      0xffff      ///<  第三个八边形，g顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_G2_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_G2_Y_MASK      0xffff0000  ///<  第三个八边形，g顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_G2_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_H2_REG         0x1ab       ///<  第三个八边形，h顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_H2_X_MASK      0xffff      ///<  第三个八边形，h顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_H2_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_H2_Y_MASK      0xffff0000  ///<  第三个八边形，h顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_H2_Y_OFFSET    16

#define REGION_SEL_CTRL_RECT_A3_REG         0x1ac       ///<  第四个八边形，a顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_A3_X_MASK      0xffff      ///<  第四个八边形，a顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_A3_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_A3_Y_MASK      0xffff0000  ///<  第四个八边形，a顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_A3_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_B3_REG         0x1ad       ///<  第四个八边形，b顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_B3_X_MASK      0xffff      ///<  第四个八边形，b顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_B3_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_B3_Y_MASK      0xffff0000  ///<  第四个八边形，b顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_B3_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_C3_REG         0x1ae       ///<  第四个八边形，c顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_C3_X_MASK      0xffff      ///<  第四个八边形，c顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_C3_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_C3_Y_MASK      0xffff0000  ///<  第四个八边形，c顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_C3_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_D3_REG         0x1af       ///<  第四个八边形，d顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_D3_X_MASK      0xffff      ///<  第四个八边形，d顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_D3_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_D3_Y_MASK      0xffff0000  ///<  第四个八边形，d顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_D3_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_E3_REG         0x1b0       ///<  第四个八边形，e顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_E3_X_MASK      0xffff      ///<  第四个八边形，e顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_E3_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_E3_Y_MASK      0xffff0000  ///<  第四个八边形，e顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_E3_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_F3_REG         0x1b1       ///<  第四个八边形，f顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_F3_X_MASK      0xffff      ///<  第四个八边形，f顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_F3_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_F3_Y_MASK      0xffff0000  ///<  第四个八边形，f顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_F3_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_G3_REG         0x1b2       ///<  第四个八边形，g顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_G3_X_MASK      0xffff      ///<  第四个八边形，g顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_G3_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_G3_Y_MASK      0xffff0000  ///<  第四个八边形，g顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_G3_Y_OFFSET    16
#define REGION_SEL_CTRL_RECT_H3_REG         0x1b3       ///<  第四个八边形，h顶点坐标寄存器
#define REGION_SEL_CTRL_RECT_H3_X_MASK      0xffff      ///<  第四个八边形，h顶点x坐标掩码
#define REGION_SEL_CTRL_RECT_H3_X_OFFSET    0
#define REGION_SEL_CTRL_RECT_H3_Y_MASK      0xffff0000  ///<  第四个八边形，h顶点y坐标掩码
#define REGION_SEL_CTRL_RECT_H3_Y_OFFSET    16

#define REGION_SEL_CTRL_RING0_REG       0x1b4       ///<  第1个环形，圆心坐标寄存器
#define REGION_SEL_CTRL_RING0_X_MASK    0xffff      ///<  第1个环形，圆心x坐标掩码
#define REGION_SEL_CTRL_RING0_X_OFFSET  0
#define REGION_SEL_CTRL_RING0_Y_MASK    0xffff0000  ///<  第1个环形，圆心y坐标掩码
#define REGION_SEL_CTRL_RING0_Y_OFFSET  16
#define REGION_SEL_CTRL_RING0_RIN_REG   0x1b5       ///<  第1个环形，小圆半径r的平方
#define REGION_SEL_CTRL_RING0_ROUT_REG  0x1b6       ///<  第1个环形，大圆半径R的平方
#define REGION_SEL_CTRL_RING1_REG       0x1b7       ///<  第2个环形，圆心坐标寄存器
#define REGION_SEL_CTRL_RING1_X_MASK    0xffff      ///<  第2个环形，圆心x坐标掩码
#define REGION_SEL_CTRL_RING1_X_OFFSET  0
#define REGION_SEL_CTRL_RING1_Y_MASK    0xffff0000  ///<  第2个环形，圆心y坐标掩码
#define REGION_SEL_CTRL_RING1_Y_OFFSET  16
#define REGION_SEL_CTRL_RING1_RIN_REG   0x1b8       ///<  第2个环形，小圆半径r的平方
#define REGION_SEL_CTRL_RING1_ROUT_REG  0x1b9       ///<  第2个环形，大圆半径R的平方
#define REGION_SEL_CTRL_RING2_REG       0x1ba       ///<  第3个环形，圆心坐标寄存器
#define REGION_SEL_CTRL_RING2_X_MASK    0xffff      ///<  第3个环形，圆心x坐标掩码
#define REGION_SEL_CTRL_RING2_X_OFFSET  0
#define REGION_SEL_CTRL_RING2_Y_MASK    0xffff0000  ///<  第3个环形，圆心y坐标掩码
#define REGION_SEL_CTRL_RING2_Y_OFFSET  16
#define REGION_SEL_CTRL_RING2_RIN_REG   0x1bb       ///<  第3个环形，小圆半径r的平方
#define REGION_SEL_CTRL_RING2_ROUT_REG  0x1bc       ///<  第3个环形，大圆半径R的平方
#define REGION_SEL_CTRL_RING3_REG       0x1bd       ///<  第4个环形，圆心坐标寄存器
#define REGION_SEL_CTRL_RING3_X_MASK    0xffff      ///<  第4个环形，圆心x坐标掩码
#define REGION_SEL_CTRL_RING3_X_OFFSET  0
#define REGION_SEL_CTRL_RING3_Y_MASK    0xffff0000  ///<  第4个环形，圆心y坐标掩码
#define REGION_SEL_CTRL_RING3_Y_OFFSET  16
#define REGION_SEL_CTRL_RING3_RIN_REG   0x1be       ///<  第4个环形，小圆半径r的平方
#define REGION_SEL_CTRL_RING3_ROUT_REG  0x1bf       ///<  第4个环形，大圆半径R的平方

#define REGION_SEL_X_SUM_REG            0x10a0      ///<  区域筛选:合格像素x坐标和
#define REGION_SEL_Y_SUM_REG            0x10a1      ///<  区域筛选:合格像素y坐标和
#define REGION_SEL_AREA_NUM_REG         0x10a2      ///<  区域筛选:合格像素数
#define REGION_SEL_TOTAL_NUM_REG        0x10a3      ///<  区域筛选:参与筛选的像素总数
#define REGION_SEL_TOTAL_GRAY_REG       0x10a4      ///<  区域筛选:合格像素数灰度值之和
#define REGION_SEL_GRAY_REG             0x10a5      ///<  区域筛选:合格像素数最小\大灰度值
#define REGION_SEL_MAX_GRAY_MASK        0xff        ///<  区域筛选，合格像素数最大灰度值
#define REGION_SEL_MAX_GRAY_OFFSET      0
#define REGION_SEL_MIN_GRAY_MASK        0xff00      ///<  区域筛选，合格像素数最小灰度值
#define REGION_SEL_MIN_GRAY_OFFSET      8

/** 区域筛选模块结果寄存器 */
#define REGION_SEL_X_SUM				0x10a0		///<  区域筛选，合格像素 x 坐标和
#define REGION_SEL_Y_SUM				0x10a1		///<  区域筛选，合格像素 Y 坐标和
#define REGION_SEL_VALID_NUM			0x10a2		///<  区域筛选，合格像素数
#define REGION_SEL_CANDIDATE_NUM		0x10a3		///<  区域筛选，参与筛选的像素总数
#define REGION_SEL_GRAY_SUM				0x10a4		///<  区域筛选，合格像素数灰度值之和
#define REGION_SEL_MIN_MAX_GRAY			0x10a5		///<  区域筛选，合格像素数最 小\大 灰度值


#define SEL_RING    g_SelectModelCfg.ring_cfg[i].ring
#define SEL_OCTAGON g_SelectModelCfg.octagons_cfg[i].octagon_vertexs[j]



typedef struct {
    unsigned int valid_x_sum;               ///< 合格像素X坐标和
    unsigned int valid_y_sum;               ///< 合格像素Y坐标和
    unsigned int valid_pixel_num;           ///< 合格像素数
    unsigned int candidate_pixel_num;       ///< 参与筛选像素总数
    unsigned int valid_pixel_gray_sum;      ///< 合格像素的灰度值和
    unsigned char  valid_pixel_gray_max;	///< 合格像素最大灰度值
    unsigned char  valid_pixel_gray_min;	///< 合格像素最小灰度值
}SELECT_MODEL_RESULT;


#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Select_Model_Init
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 区域筛选模块参数初始化
 */
DLLSHARED_EXPORT int Select_Model_Init(u32 acce_index);

/**
 * @brief Select_Model_Param_Set
 * @param acce_index: 步骤索引号
 * @author Vincent
 * @date 2017/5/12
 * @note 区域筛选模块参数设置
 */
DLLSHARED_EXPORT int Select_Model_Param_Set(u32 acce_index);

/**
 * @brief Select_Model_Input_Model_Get
 * @param acce_index: 步骤索引号
 * @return
 * @author Vincent
 * @date 2017/5/12
 * @note 区域筛选模块输入源获取
 */
DLLSHARED_EXPORT int Select_Model_Input_Model_Get(unsigned int acce_index);

/**
 * @brief Select_Model_Output_Get
 * @param acce_index: 步骤索引号
 * @param output_type
 * @param pContainer
 * @author Vincent
 * @date 2017/5/12
 * @note 区域筛选模块输出参数获取
 */
DLLSHARED_EXPORT void Select_Model_Output_Get(unsigned int acce_index, unsigned int output_type, void *pContainer);

/**
 * @brief Select_Model_Disable
 * @author Vincent
 * @date 2017/5/12
 * @note 区域筛选模块功能关闭
 */
DLLSHARED_EXPORT void Select_Model_Disable(void);

/**
 * @brief Select_Model_Enable
 * @author Vincent
 * @date 2017/5/12
 * @note 区域筛选模块使能打开
 */
DLLSHARED_EXPORT void Select_Model_Enable(void);

/**
 * @brief Select_Model_Write_DDR_On
 * @param acce_index
 * @author Vincent
 * @date 2017/5/12
 * @note 区域筛选写DDR使能打开
 */
DLLSHARED_EXPORT void Select_Model_Write_DDR_On(unsigned int acce_index);

/**
 * @brief Select_Model_Write_DDR_Off
 * @author Vincent
 * @date 2017/5/12
 * @note 区域筛选模块写DDR使能关闭
 */
DLLSHARED_EXPORT void Select_Model_Write_DDR_Off(void);

/**
 * @brief Select_Model_Reg_Show
 * @author Vincent
 * @date 2017/6/15
 * @note 区域筛选模块寄存器数据打印函数
 */
DLLSHARED_EXPORT void Select_Model_Reg_Show(void);

/**
 * @brief Select_Model_Src_Sel
 * @param acce_index
 * @param acce_id
 * @author Vincent
 * @date 2017/6/1
 * @note 区域筛选模块寄存器图像源设置函数
 */
DLLSHARED_EXPORT inline void Select_Model_Src_Sel(unsigned int acce_index, unsigned int acce_id);

/**
 * @brief Select_Model_Compass_Result_Set
 * @param acce_index: 步骤索引号
 * @param valid_flag: 参数有效标志
 * @param sel_model: 关联定位后的参数
 * @return 0: 成功 -1: 失败
 * @author Vincent
 * @date 2017/7/12
 * @note 区域筛选模块关联定位后的结果设置
 */
DLLSHARED_EXPORT int Select_Model_Compass_Result_Set(unsigned int acce_index, unsigned int valid_flag, SELECT_MODEL_CFG * sel_model);

/**
 * @brief Select_Model_Compass_Result_Get
 * @param acce_index：步骤索引号
 * @param sel_model：选择区域的参数结构体指针
 * @return 0: 成功 Other: 失败
 * @author Vincent
 * @date 2017/5/12
 * @note 区域筛选模块关联定位后的结果获取
 */
DLLSHARED_EXPORT int Select_Model_Compass_Result_Get(unsigned int acce_index, SELECT_AREA_PARAM * sel_model);

/**
 * @brief Check_Step_Select_Model
 * @param acce_index: 步骤索引号
 * @param sel_model: 接收区域筛选参数的指针
 * @return 1: 使用了区域筛选 0: 未使用区域筛选 -1: 传入指针为NULL
 * @author Vincent
 * @date 2017/7/12
 * @note 检查指定步骤是否使用区域筛选
 */
DLLSHARED_EXPORT int Check_Step_Select_Model(unsigned int acce_index, SELECT_MODEL_CFG * sel_model);

DLLSHARED_EXPORT void Set_Select_Background_Color_Sel(u32 num);
DLLSHARED_EXPORT void Set_Select_Color_Pic_Wr_Ddr_Addr(u32 addr);
DLLSHARED_EXPORT void Set_Select_Color_Pic_Wr_Enable(u32 flag);
DLLSHARED_EXPORT void Set_Select_Enable(u32 flag);
DLLSHARED_EXPORT void Set_Select_Mono_Pic_Wr_Enable(u32 flag);
DLLSHARED_EXPORT void Set_Select_Octagon0_Inv_En(u32 num);
DLLSHARED_EXPORT void Set_Select_Octagon1_Inv_En(u32 num);
DLLSHARED_EXPORT void Set_Select_Octagon2_Inv_En(u32 num);
DLLSHARED_EXPORT void Set_Select_Octagon3_Inv_En(u32 num);
DLLSHARED_EXPORT void Set_Select_Octagon_0_Vertexs(VERTEX_POINT * vertexs);
DLLSHARED_EXPORT void Set_Select_Octagon_0_Vertex_En(u32 num);
DLLSHARED_EXPORT void Set_Select_Octagon_1_Vertexs(VERTEX_POINT * vertexs);
DLLSHARED_EXPORT void Set_Select_Octagon_1_Vertex_En(u32 num);
DLLSHARED_EXPORT void Set_Select_Octagon_2_Vertexs(VERTEX_POINT * vertexs);
DLLSHARED_EXPORT void Set_Select_Octagon_2_Vertex_En(u32 num);
DLLSHARED_EXPORT void Set_Select_Octagon_3_Vertexs(VERTEX_POINT * vertexs);
DLLSHARED_EXPORT void Set_Select_Octagon_3_Vertex_En(u32 num);
DLLSHARED_EXPORT void Set_Select_Ring0_En(u32 num);
DLLSHARED_EXPORT void Set_Select_Ring0_Inv_En(u32 num);
DLLSHARED_EXPORT void Set_Select_Ring1_En(u32 num);
DLLSHARED_EXPORT void Set_Select_Ring1_Inv_En(u32 num);
DLLSHARED_EXPORT void Set_Select_Ring2_En(u32 num);
DLLSHARED_EXPORT void Set_Select_Ring2_Inv_En(u32 num);
DLLSHARED_EXPORT void Set_Select_Ring3_En(u32 num);
DLLSHARED_EXPORT void Set_Select_Ring3_Inv_En(u32 num);
DLLSHARED_EXPORT void Set_Select_Ring_0(CIRCULAR * ring);
DLLSHARED_EXPORT void Set_Select_Ring_1(CIRCULAR * ring);
DLLSHARED_EXPORT void Set_Select_Ring_2(CIRCULAR * ring);
DLLSHARED_EXPORT void Set_Select_Ring_3(CIRCULAR * ring);
DLLSHARED_EXPORT void Set_Select_Src_Sel(u32 num);
DLLSHARED_EXPORT u32 Get_Select_Ref_Value(void);


DLLSHARED_EXPORT inline void REGION_SEL_CTRL_COLOR_WR_ADDR(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_COLOR_WR_DDR_DISABLE(void);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_COLOR_WR_DDR_ENABLE(void);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_DISABLE(void);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_ENABLE(void);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_MONO_WR_DDR_DISABLE(void);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_MONO_WR_DDR_ENABLE(void);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_POLYGON0_ENABLE(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_POLYGON0_INV(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_POLYGON1_ENABLE(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_POLYGON1_INV(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_POLYGON2_ENABLE(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_POLYGON2_INV(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_POLYGON3_ENABLE(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_POLYGON3_INV(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_A0_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_A0_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_A1_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_A1_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_A2_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_A2_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_A3_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_A3_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_B0_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_B0_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_B1_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_B1_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_B2_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_B2_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_B3_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_B3_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_C0_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_C0_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_C1_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_C1_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_C2_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_C2_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_C3_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_C3_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_D0_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_D0_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_D1_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_D1_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_D2_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_D2_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_D3_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_D3_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_E0_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_E0_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_E1_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_E1_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_E2_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_E2_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_E3_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_E3_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_F0_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_F0_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_F1_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_F1_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_F2_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_F2_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_F3_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_F3_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_G0_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_G0_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_G1_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_G1_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_G2_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_G2_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_G3_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_G3_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_H0_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_H0_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_H1_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_H1_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_H2_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_H2_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_H3_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RECT_H3_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RGB_BACK(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING0_ENABLE(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING0_INV_ENABLE(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING0_RIN(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING0_ROUT(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING0_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING0_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING1_ENABLE(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING1_INV_ENABLE(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING1_RIN(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING1_ROUT(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING1_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING1_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING2_ENABLE(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING2_INV_ENABLE(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING2_RIN(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING2_ROUT(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING2_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING2_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING3_ENABLE(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING3_INV_ENABLE(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING3_RIN(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING3_ROUT(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING3_X(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_RING3_Y(u32 num);
DLLSHARED_EXPORT inline void REGION_SEL_CTRL_SRC_SEL(u32 src);

#ifdef __cplusplus
}
#endif

#endif // AREASELECT_H
