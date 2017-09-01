/**
  * @file  [Code39.h]
  * @brief  Code39码扫描函数
  * @author  <th>
  * @date  <2017/8/2>
  * @version  <v1.0>
  * @note
  *
  */


#ifndef CODE39_H_
#define CODE39_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

extern int Code39_Decode(char *raw, int width, int height, int status,  char *Code_Rst, unsigned int *Length);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif





