#ifndef CODABARCODE_H
#define CODABARCODE_H

#include <stdlib.h>
#include <stdio.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

int CodaBar_Decode(char* image, int width, int height, int status, char* Code_Rst, unsigned int *Length);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif // CODABARCODE_H
