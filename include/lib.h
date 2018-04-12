#ifndef OUR_LIB_H
#define OUR_LIB_H

#include <am.h>
#include <amdev.h>
#include <stdarg.h>

#define bool char
#define true 1
#define false 0
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

/**************************/
/*        stdio.h        */
/**************************/
int printf(char *fmt, ...);


/**************************/
/*        string.h        */
/**************************/
int strlen(const char *str);
void *memset(void * s, int c, size_t count);


/**************************/
/*         math.h         */
/**************************/
int abs(int num);


/**************************/
/*        stdlib.h        */
/**************************/
int rand(void);
void srand(unsigned int seed);
char *itoa(int num, char *str, int radix, int sign);
int atoi(char* pstr);


#endif
