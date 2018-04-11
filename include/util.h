#ifndef OUR_UTIL_H
#define OUR_UTIL_H

#include "lib.h"
#include "fb.h"
#include "model.h"
#include "io_util.h"

#define TRUE 1
#define FALSE 0
#define bool char
#define DWORD unsigned
#define WORD unsigned short
#define LONG int
#ifndef NULL
#define NULL 0
#endif 

//不采用sizeof而是宏定义大小是因为sizeof考虑了对齐
#define BITMAPFILEHEADER_LENGTH 14
#define SIZE_OF_OBJECTSET 24
#define _WIDTH 400
#define _HEIGHT 300
#define PLANE_HEIGHT 50
#define DEFAULT_COLOR 0x01000000
#define BACKGROUND 0x00010101


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

enum {ID_PLAYER, ID_ENEMY_SMALL, ID_ENEMY_MEDIUM, ID_ENEMY_BIG, ID_ROUNDBULLET_0, ID_ROUNDBULLET_1, ID_DOWNMISSILE, ID_UPMISSILE, ID_SMALLBOMB_0, ID_SMALLBOMB_1, ID_SMALLBOMB_2, ID_SMALLBOMB_3, ID_SMALLBOMB_4, ID_SMALLBOMB_5, ID_SMALLBOMB_6, ID_SMALLBOMB_7, ID_BIGBOMB_0, ID_BIGBOMB_1, ID_BIGBOMB_2, ID_BIGBOMB_3, ID_BIGBOMB_4, ID_BIGBOMB_5, ID_BIGBOMB_6, ID_BIGBOMB_7};

typedef struct {
	int x, y;
	uint32_t w, h;
} UTIL_RECT;

typedef struct RES_IDC {
    int ID;
    UTIL_RECT rect;
}RES_IDC;

typedef struct tagBITMAPFILEHEADER {
	WORD  bfType;
	DWORD bfSize;
	WORD  bfReserved1;
	WORD  bfReserved2;
	DWORD bfOffBits;
} BITMAPFILEHEADER, *PBITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER {
	DWORD biSize;
	LONG  biWidth;
	LONG  biHeight;
	WORD  biPlanes;
	WORD  biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG  biXPelsPerMeter;
	LONG  biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
    char pixels[];
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

RES_IDC res_idc[SIZE_OF_OBJECTSET];

unsigned color_buf[_WIDTH * _HEIGHT];
unsigned color_to_int(Color color);
Color int_to_color(int rgb);

#endif
