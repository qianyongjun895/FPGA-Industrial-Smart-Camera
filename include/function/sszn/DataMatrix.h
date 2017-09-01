/**
  * @file  [DataMatrix.h]
  * @brief  DataMatrix码扫描函数
  * @author  <th>
  * @date  <2017/8/2>
  * @version  <v1.0>
  * @note
  *
  */
#ifndef DATAMATRIX_H_
#define DATAMATRIX_H_
	
#ifdef __cplusplus
#if __cplusplus
	extern "C"{
#endif
#endif /* __cplusplus */


extern int DataMatrix_Decode(char *raw, int width, int height, unsigned int scale, int status, char *Code_Rst, unsigned int *Length);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif


