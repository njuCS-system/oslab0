#ifndef PLANEX_H
#define PLANEX_H

#include "util.h"
#include "hp.h"

#define PLANEX_MAX 20


typedef struct PlaneXProperty{
    int x,y; //位置
    int vx, vy;
    int size;
    int hp_max;
    int attack;
}PlaneXProperty;


typedef struct PlaneX{
    volatile Info info;
    volatile PlaneXProperty property;
    Hp *hp;
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
void planeX_locate(PlaneX *, UTIL_RECT*);

//
void planeX_automove(PlaneX* planeX);

//
void planeX_hurt(PlaneX*, int);

//
bool planeX_isCrash(PlaneX*);

//
int planeX_get_attack(PlaneX *);

//
void planeX_set_attack(PlaneX *, int);

//
int planeX_get_hp(PlaneX *);

#endif
