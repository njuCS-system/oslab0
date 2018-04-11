#ifndef PLANET_H
#define PLANET_H

#include "util.h"
#include "hp.h"


#define PLANET_MAX 20


typedef struct PlaneTProperty{
    int x,y; //位置
    int vx, vy;
    int size;
    int hp_max;
}PlaneTProperty;


typedef struct PlaneT{
    volatile Info info;
    volatile PlaneTProperty property;
    Hp *hp;
}PlaneT;

typedef struct PlaneT_factory{
    PlaneT __planeTs[PLANET_MAX];
    int idx;
}PlaneT_factory;


PlaneT *build_planeT();

//*******************virtual functions***********************

//绘制
void planeT_draw(PlaneT* );

//移动
void planeT_move(PlaneT*,int,int);

//删除
void planeT_delete(PlaneT* );

//
void planeT_locate(PlaneT *, UTIL_RECT*);

//
void planeT_automove(PlaneT* planeT);

//
void planeT_hurt(PlaneT*, int);


#endif
