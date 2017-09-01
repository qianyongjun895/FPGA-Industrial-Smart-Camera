/**
  * @file  [EAN8.h]
  * @brief  EAN8码扫描函数
  * @author  <th>
  * @date  <2017/8/2>
  * @version  <v1.0>
  * @note
  *
  */


#ifndef EAN8_H_
#define EAN8_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

extern int EAN8_Decode(char *raw, int width, int height, int status,  char *Code_Rst, unsigned int *Length);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

