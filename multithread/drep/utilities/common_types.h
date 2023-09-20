#ifndef _COMMON_TYPE_H
#define _COMMON_TYPE_H

typedef signed char         INT8;
typedef short int           INT16;
typedef int                 INT32;
typedef long long int       INT64;

typedef unsigned char       UINT8;
typedef unsigned short int  UINT16;
typedef unsigned int        UINT32;
typedef unsigned long long  UINT64;

typedef unsigned long       ADDR;
typedef unsigned int        ADDR32;

typedef unsigned int        INSINDEX;
typedef unsigned int        BBINDEX;
typedef unsigned int        BBLKINDEX;
typedef unsigned int        FUNINDEX;
typedef unsigned int        CLSTINDEX;

typedef unsigned int        OUTLPINDEX;
typedef unsigned int        INNLPINDEX;
typedef unsigned int        REGIONINDEX;
typedef unsigned int        REMINDEX;
typedef unsigned int        RMINSINDEX;

typedef unsigned int        SMPLINDEX;
typedef int            INDEX;

typedef enum {FALSE, TRUE} BOOL;

typedef unsigned int    ELEM_TYPE;

typedef enum
{ cINV, cREP, cREPE, cREPNE,cLOCK } PREFIX;

#endif

