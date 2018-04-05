#ifndef RECT_H
#define RECT_H

#include "util.h"


#define RECT_MAX 100


typedef struct RectProperty{
    int x,y,width,height; //位置和大小
    char r,g,b;//颜色
    int stroke;//线宽
}RectProperty;


typedef struct Rect{
    volatile Info info;
    volatile RectProperty property;
}Rect;

typedef struct Rect_factory{
    Rect __rects[RECT_MAX];
    int idx;
    Rect* (*build)(RectProperty property);
    void (*free)(Rect*);
}Rect_factory;


Rect* build_rect();

//*******************virtual functions***********************

//绘制矩形
void rect_draw(Rect* );

//移动矩形
void rect_move(Rect*,int,int);

//删除矩形
void rect_delete(Rect* );




#endif