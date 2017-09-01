#ifndef ITFCODE_H
#define ITFCODE_H

#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

int ITF_Decode(char* image, int width, int height, int status, char* Code_Rst, unsigned int *Length);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif // ITFCODE_H
