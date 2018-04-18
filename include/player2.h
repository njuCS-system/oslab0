#ifndef PLAYER2_H
#define PLAYER2_H

#include "util.h"
#include "hp.h"

#define PLAYER2_MAX 20
#define PLAYER2_SPEED 12

typedef struct Player2Property{
    int x,y; //位置
    int size;
    int hp_max;
    int attack;
}Player2Property;


typedef struct Player2{
    volatile Info info;
    volatile Player2Property property;
    Hp *hp;
}Player2;

typedef struct Player2_factory{
    Player2 __player2s[PLAYER2_MAX];
    int idx;
}Player2_factory;


Player2 *build_player2();

//*******************virtual functions***********************

//绘制
void player2_draw(Player2* );

//移动
void player2_move(Player2*,int,int);

//删除
void player2_delete(Player2* );

//
void player2_locate(Player2 *, UTIL_RECT*);

//
void player2_automove(Player2* player2);

//
void player2_answer(Player2*, int keycode);

//
void player2_hurt(Player2*, int);

//
bool player2_isCrash(Player2*);

//
int player2_get_attack(Player2 *);

//
void player2_set_attack(Player2 *, int);

//
int player2_get_hp(Player2 *);


#endif
