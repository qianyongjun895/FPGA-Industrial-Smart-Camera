/**
  * @file  [Code128.h]
  * @brief  Code128码扫描函数
  * @author  <th>
  * @date  <2017/8/2>
  * @version  <v1.0>
  * @note
  *
  */


#ifndef CODE128_H_
#define CODE128_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

extern int Code128_Decode(char *raw, int width, int height, int status,  char *Code_Rst, unsigned int *Length);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

