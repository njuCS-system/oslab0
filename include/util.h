#ifndef OUR_UTIL_H
#define OUR_UTIL_H

#include "lib.h"
#include "fb.h"
#define TRUE 1
#define FALSE 0
#define bool char
#ifndef NULL
#define NULL 0
#endif 

#define _WIDTH 400
#define _HEIGHT 300
#define DEFAULT_COLOR 0x01000000
 

typedef struct Info{
    volatile char type;//record the type of an object
    volatile bool valid;

}Info;

typedef struct Color{
    volatile unsigned char b;
    volatile unsigned char g;
    volatile unsigned char r;
    volatile unsigned char a;
}Color;

unsigned color_buf[_WIDTH * _HEIGHT];

unsigned color_to_int(Color color);

/*_Device *getdev(_Device **ptr, uint32_t id);
_Device *video_dev;

void draw_sync();
*/

#endif
