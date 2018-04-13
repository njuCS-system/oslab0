#ifndef PLANEI_H
#define PLANEI_H

#include "util.h"
#include "hp.h"


#define PLANEI_MAX 20


typedef struct PlaneIProperty{
    int x,y; //位置
    int vx, vy;
    int size;
    int hp_max;
    int attack;
}PlaneIProperty;


typedef struct PlaneI{
    volatile Info info;
    volatile PlaneIProperty property;
    Hp *hp;
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
void planeI_locate(PlaneI *, UTIL_RECT*);

//
void planeI_automove(PlaneI* planeI);

//
void planeI_hurt(PlaneI*, int);

//
bool planeI_isCrash(PlaneI*);

//
int planeI_get_attack(PlaneI *);

//
void planeI_set_attack(PlaneI *, int);

//
int planeI_get_hp(PlaneI *);


#endif
