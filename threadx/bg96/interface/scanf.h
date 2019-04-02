/*
 * scanf.h
 *
 *  Created on: 27.06.2018
 *      Author: georgi.angelov
 */

#ifndef SCANF_H_
#define SCANF_H_


#include <sys/types.h>
#include <stdarg.h>
#include "common.h"

#undef sscanf
EXTERN_C int sscanf(const char *ibuf, const char *fmt, ...);

#endif /* SCANF_H_ */
