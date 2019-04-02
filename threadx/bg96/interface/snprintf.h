/*
	ftp://ftp.dante.de/tex-archive/graphics/sam2p/snprintf.h
	Georgi Angelov 18.04.2018
*/

#ifndef SNPRINTF_H
#define SNPRINTF_H 1

#include <sys/types.h>
#include <stdarg.h>
#include "common.h"

#undef vsnprintf
EXTERN_C int		a_vsnprintf(char *__restrict, size_t, const char *__restrict, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 3, 0)));
#define vsnprintf 	a_vsnprintf

#undef vsprintf
EXTERN_C int		a_vsprintf(char *__restrict, const char *__restrict, __gnuc_va_list) __attribute__ ((__format__ (__printf__, 2, 0)));
#define vsprintf 	a_vsprintf

#undef sprintf
EXTERN_C int		a_sprintf(char *__restrict, const char *__restrict, ...) __attribute__ ((__format__ (__printf__, 2, 3)));
#define sprintf 	a_sprintf

#undef snprintf
EXTERN_C int     	a_snprintf(char *__restrict, size_t, const char *__restrict, ...) __attribute__ ((__format__ (__printf__, 3, 4)));
#define snprintf 	a_snprintf

#endif /* snprintf.h */


