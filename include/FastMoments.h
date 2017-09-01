/**
  * @file  [FastMoments.h]
  * @brief 快速计算矩、Hu矩
  * @author  <Terry>
  * @date  <2017/06/02>
  * @version  <v1.0>
  * @note
  */

#ifndef FAST_MOMENTS_H
#define FAST_MOMENTS_H

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
#include "sszn_basic.h"
#include "roi.h"
#include "Link.h"

/**
 * @brief 计算满足门限要求的连通域个数
 * @param pThreshold：门限指针
 * @param pLinkNum：个数保存位置
 * @return 是否成功获取连通域个数
 * @author <Terry>
 * @note
 */
int LinkCountGetThBySize(THRESHOLD_INT *pThSize, unsigned int *pLinkNum);

/**
 * @brief FPGA输出结果转化成计算矩的参数
 * @param pLinkFpgaRst：FPGA的连通域结果输出
 * @param pLinkRst：计算连通域矩的中间结构体
 * @return 
 * @author <Terry>
 * @note
 */
void FpgaLinkRst2LinkRst(LINK_FPGA_RESULT *pFpgaLinkRst, LINK_RESULT *pLinkRst);

/**
 * @brief 计算矩
 * @param pLinkRst：计算连通域矩的中间结构体
 * @param pMoments：矩指针
 * @return 
 * @author <Terry>
 * @note
 */
int MomentsCalc(LINK_RESULT *pLinkRst, roiMoments *pMoments);

/**
 * @brief 计算Hu矩
 * @param pMoments：矩指针
 * @param pHuMoments：Hu矩指针
 * @return 
 * @author <Terry>
 * @note
 */
int HuMomentsCalc(roiMoments *pMoments, HuMoments *pHuMoments);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif // FAST_MOMENTS_H

