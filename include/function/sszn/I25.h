/**
  * @file  [I25.h]
  * @brief  I2/5码扫描函数
  * @author  <th>
  * @date  <2017/8/2>
  * @version  <v1.0>
  * @note
  *
  */


#ifndef I25_H_
#define I25_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

extern int I25_Decode(char *raw, int width, int height, int status,  char *Code_Rst, unsigned int *Length);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif


