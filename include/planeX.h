#ifndef PLANEX_H
#define PLANEX_H

#include "util.h"
#include "rect.h"


#define PLANEX_MAX 20


typedef struct PlaneXProperty{
    int x,y; //位置
    int vx, vy;
    int size;
}PlaneXProperty;


typedef struct PlaneX{
    volatile Info info;
    volatile PlaneXProperty property;
    Rect *large_wing;
    Rect *small_wing;
    Rect *empennage_left;
    Rect *empennage_right;
    Rect *body;
    Rect *jet_left;
    Rect *jet_right;
}PlaneX;

typedef struct PlaneX_factory{
    PlaneX __planeXs[PLANEX_MAX];
    int idx;
}PlaneX_factory;


PlaneX *build_planeX();

//*******************virtual functions***********************

//绘制
void planeX_draw(PlaneX* );

//移动
void planeX_move(PlaneX*,int,int);

//删除
void planeX_delete(PlaneX* );

//
void planeX_automove(PlaneX* planeX);




#endif
