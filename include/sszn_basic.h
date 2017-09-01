#ifndef __SSZN_BASIC_H_
#define __SSZN_BASIC_H_
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include "BaseStruct.h"
#include "ErrorCode.h"
#include "Debug.h"
#include "threshold.h"
#include "BlockInfo.h"
#include "PixelConvert.h"
#include "MultipointDemarcate.h"
#include "MultiCmosParam.h"
#include "ScaleRatio.h"
#include "License.h"
#include "NetWorkSet.h"
#include "RstData.h"


int SystemCmd(const char * pCmd);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif
