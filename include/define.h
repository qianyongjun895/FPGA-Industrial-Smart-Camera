#ifndef DEFINE__H
#define DEFINE__H

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#ifndef WIN32
#ifndef bool
#define bool char
#endif /* #ifndef bool */
#endif /* #ifndef WIN32 */

#ifndef BOOL
#define BOOL int
#endif /* #ifndef BOOL */

#ifndef u8
#define u8 unsigned char
#endif

#ifndef u16
#define u16 unsigned short
#endif

#ifndef u32
#define u32 unsigned int
#endif

#ifndef u64
#define u64 unsigned long long int
#endif

#ifndef s8
#define s8 char
#endif

#ifndef s16
#define s16 short
#endif

#ifndef s32
#define s32 int
#endif

#ifndef s64
#define s64 long long int
#endif

#ifndef f32
#define f32 float
#endif

#ifndef d64
#define d64 double
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#  ifdef __cplusplus
#  define NULL        (0L)
#  else /* !__cplusplus */
#  define NULL        ((void*) 0)
#  endif /* !__cplusplus */
#endif


//#define PROJECTNAME 0X00000021

#ifdef WIN32
#define  DLLSHARED_EXPORT __declspec(dllexport)
#else
#define  DLLSHARED_EXPORT extern

#endif

#ifndef ASSERT
#define ASSERT(expression, z, message, ...)  if((expression))\
    {\
        printf("FILE: "__FILE__", LINE: %d: "message"\n", __LINE__, ##__VA_ARGS__);\
        return z;\
    }
#endif

#define CHECK_RESULT(condition,output,ret)  if(condition)\
    {\
        printf("COMM: in function %s %s\n",__FUNCTION__,output);\
        return ret;\
    }
#define CHECK_do_RESULT(condition,do_it,output,ret)	if(condition)\
    {\
        do_it;\
        printf("COMM: in function %s %s\n",__FUNCTION__,output);\
        return ret;\
    }
#define CHECK_PARAME(condition,output,ret)	if(condition)\
    {\
        printf("COMM: in function %s parameter %d error\n",__FUNCTION__,output);\
        return ret;\
    }
#define IF_STATEMENT_DO(condition,do_it)    if(condition)\
    {\
        do_it;\
    }
#define IF_STATEMENT_RETURN(condition,ret)	if(condition)\
    {\
        return ret;\
    }
#define IF_STATEMENT_DO_RETURN(condition,do_it,ret) if(condition)\
    {\
        do_it;\
        printf("COMM: in function %s %s \n",__FUNCTION__,condition);\
        return ret;\
    }
#define IF_STATEMENT_DO_RET(condition,do_it,ret)    if(condition)\
    {\
        do_it;\
        return ret;\
    }

#define IF_DO(condition,do_it)	if(condition)\
    {\
        do_it;\
    }
#define IF_DO_RETURN(condition,do_it,ret)   if(condition)\
    {\
        do_it;\
        return ret;\
    }
#define ELSE_IF_DO(condition,do_it)	else if(condition)\
    {\
        do_it;\
    }
#define ELSE_IF_DO_RETURN(condition,do_it,ret)  else if(condition)\
    {\
        do_it;\
        return ret;\
    }
#define ELSE_DO(do_it)  else\
    {\
        do_it;\
    }
#define ELSE_DO_RETURN(do_it,ret)   else\
    {\
        do_it;\
        return ret;\
    }
#define CHECK_RETURN_VALUE(a,b,c)   if(a)					\
    {						\
        printf(b);		\
        return c;		\
    }

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
	
#endif
