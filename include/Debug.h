#ifndef _DEBUG_PRINT_H
#define _DEBUG_PRINT_H

#include <stdio.h>
#include <sys/types.h>

#define ACCE_DEBUG      		((unsigned int)1<<0)   // 0x00000001
#define HARDWARE_DEBUG      	((unsigned int)1<<1)   // 0x00000002
#define CMOS_DEBUG      		((unsigned int)1<<2)   // 0x00000004
#define RUN_DEBUG      			((unsigned int)1<<3)   // 0x00000008
#define EDIT_DEBUG              ((unsigned int)1<<4)   // 0x00000010
#define PRINT_TYPE_UNUSE_6      ((unsigned int)1<<5)   // 0x00000020
#define PRINT_TYPE_UNUSE_7      ((unsigned int)1<<6)   // 0x00000040
#define PRINT_TYPE_UNUSE_8      ((unsigned int)1<<7)   // 0x00000080
#define PRINT_TYPE_UNUSE_9      ((unsigned int)1<<8)   // 0x00000100
#define PRINT_TYPE_UNUSE_10     ((unsigned int)1<<9)   // 0x00000200
#define PRINT_TYPE_UNUSE_11     ((unsigned int)1<<10)  // 0x00000400
#define PRINT_TYPE_UNUSE_12     ((unsigned int)1<<11)  // 0x00000800
#define PRINT_TYPE_UNUSE_13     ((unsigned int)1<<12)  // 0x00001000
#define PRINT_TYPE_UNUSE_14     ((unsigned int)1<<13)  // 0x00002000
#define PRINT_TYPE_UNUSE_15     ((unsigned int)1<<14)  // 0x00004000
#define PRINT_TYPE_UNUSE_16     ((unsigned int)1<<15)  // 0x00008000
#define PRINT_TYPE_UNUSE_17     ((unsigned int)1<<16)  // 0x00010000
#define PRINT_TYPE_UNUSE_18     ((unsigned int)1<<17)  // 0x00020000
#define PRINT_TYPE_UNUSE_19     ((unsigned int)1<<18)  // 0x00040000
#define PRINT_TYPE_UNUSE_20     ((unsigned int)1<<19)  // 0x00080000
#define PRINT_TYPE_UNUSE_21     ((unsigned int)1<<20)  // 0x00100000
#define PRINT_TYPE_UNUSE_22     ((unsigned int)1<<21)  // 0x00200000
#define PRINT_TYPE_UNUSE_23     ((unsigned int)1<<22)  // 0x00400000
#define PRINT_TYPE_UNUSE_24     ((unsigned int)1<<23)  // 0x00800000
#define PRINT_TYPE_UNUSE_25     ((unsigned int)1<<24)  // 0x01000000
#define PRINT_TYPE_UNUSE_26     ((unsigned int)1<<25)  // 0x02000000
#define PRINT_TYPE_UNUSE_27     ((unsigned int)1<<26)  // 0x04000000
#define PRINT_TYPE_UNUSE_28     ((unsigned int)1<<27)  // 0x08000000
#define PRINT_TYPE_UNUSE_29     ((unsigned int)1<<28)  // 0x10000000
#define PRINT_TYPE_UNUSE_30     ((unsigned int)1<<29)  // 0x20000000
#define PRINT_TYPE_UNUSE_31     ((unsigned int)1<<30)  // 0x40000000
#define PRINT_TYPE_UNUSE_32     ((unsigned int)1<<31)  // 0x80000000


#define DRV_DEBUG
#ifdef DRV_DEBUG
void SetDebugFlag(unsigned int flag);
unsigned int GetDebugFlag(void);
#define DRV_PRINT(printType, format, ...) \
{\
    if((GetDebugFlag() & (unsigned int)printType))\
    {\
        printf("FILE: "__FILE__", LINE: %d: "format"\n", __LINE__, ##__VA_ARGS__);\
    }\
}
#else
#define DRV_PRINT(printType, format, ...)
#endif

#endif
