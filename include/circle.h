#ifndef CIRCLE_H
#define CIRCLE_H

#include "util.h"


#define CIRCLE_MAX 200


typedef struct CircleProperty{
    int x,y,r; //位置和大小
    Color color;//颜色
}CircleProperty;


typedef struct Circle{
    volatile Info info;
    volatile CircleProperty property;
}Circle;

typedef struct Circle_factory{
    Circle __circles[CIRCLE_MAX];
    int idx;
}Circle_factory;


Circle* build_circle();

//*******************virtual functions***********************

//绘制
void circle_draw(Circle* );

//移动
void circle_move(Circle*,int,int);

//删除
void circle_delete(Circle* );




#endif
