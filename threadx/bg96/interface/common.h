/*
 * common.h
 *
 *  Created on: 11.06.2018
 *      Author: 1124
 */

#ifndef COMMON_H_
#define COMMON_H_

#ifndef __cplusplus
#  define EXTERN_C extern
#else
#  define EXTERN_C extern "C"
#endif

EXTERN_C int strStartsWith(const char *line, const char *prefix);
EXTERN_C int inet_ntoa(const unsigned int inaddr, unsigned char * buf, unsigned int len);

#endif /* COMMON_H_ */
