#ifndef RECT_H
#define RECT_H

#include "util.h"


#define RECT_MAX 200


typedef struct RectProperty{
    int x,y,width,height; //位置和大小
    Color s_color;//颜色
    Color f_color;
    int stroke;//线宽
    bool is_fill;
}RectProperty;


typedef struct Rect{
    volatile Info info;
    volatile RectProperty property;
}Rect;

typedef struct Rect_factory{
    Rect __rects[RECT_MAX];
    int idx;
}Rect_factory;


Rect* build_rect();

//*******************virtual functions***********************

//绘制
void rect_draw(Rect* );

//移动
void rect_move(Rect*,int,int);

//删除
void rect_delete(Rect* );




#endif
