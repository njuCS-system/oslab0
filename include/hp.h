#ifndef HP_H
#define HP_H

#include "util.h"
#include "rect.h"

#define HP_MAX 200


typedef struct HpProperty{
    int x,y; //位置
    int size;
    int hp_max;
    bool is_player;
}HpProperty;


typedef struct Hp{
    volatile Info info;
    volatile HpProperty property;
    int hp_left;
}Hp;

typedef struct Hp_factory{
    Hp __hps[HP_MAX];
    int idx;
}Hp_factory;


Hp* build_hp();

//*******************virtual functions***********************

//绘制
void hp_draw(Hp* );

//移动
void hp_move(Hp*,int,int);

//删除
void hp_delete(Hp* );

//
void hp_decrease(Hp*, int);




#endif
