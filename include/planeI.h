#ifndef PLANEI_H
#define PLANEI_H

#include "util.h"
#include "rect.h"


#define PLANEI_MAX 20


typedef struct PlaneIProperty{
    int x,y; //位置
    int vx, vy;
    int size;
}PlaneIProperty;


typedef struct PlaneI{
    volatile Info info;
    volatile PlaneIProperty property;
    Rect *large_wing;
    Rect *small_wing;
    Rect *empennage_left;
    Rect *empennage_right;
    Rect *body;
    Rect *jet_left;
    Rect *jet_right;
}PlaneI;

typedef struct PlaneI_factory{
    PlaneI __planeIs[PLANEI_MAX];
    int idx;
}PlaneI_factory;


PlaneI *build_planeI();

//*******************virtual functions***********************

//绘制
void planeI_draw(PlaneI* );

//移动
void planeI_move(PlaneI*,int,int);

//删除
void planeI_delete(PlaneI* );

//
void planeI_automove(PlaneI* planeI);




#endif
