#ifndef PLANEU_H
#define PLANEU_H

#include "util.h"
#include "hp.h"


#define PLANEU_MAX 20


typedef struct PlaneUProperty{
    int x,y; //位置
    int vx, vy;
    int size;
    int hp_max;
    int attack;
}PlaneUProperty;


typedef struct PlaneU{
    volatile Info info;
    volatile PlaneUProperty property;
    Hp *hp;
}PlaneU;

typedef struct PlaneU_factory{
    PlaneU __planeUs[PLANEU_MAX];
    int idx;
}PlaneU_factory;


PlaneU *build_planeU();

//*******************virtual functions***********************

//绘制
void planeU_draw(PlaneU* );

//移动
void planeU_move(PlaneU*,int,int);

//删除
void planeU_delete(PlaneU* );

//
void planeU_locate(PlaneU *, UTIL_RECT*);

//
void planeU_automove(PlaneU* planeU);

//
void planeU_hurt(PlaneU*, int);

//
bool planeU_isCrash(PlaneU*);

//
int planeU_get_attack(PlaneU *);

//
void planeU_set_attack(PlaneU *, int);


#endif
