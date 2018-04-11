#ifndef PLAYER1_H
#define PLAYER1_H

#include "util.h"
#include "hp.h"

#define PLAYER1_MAX 20
#define PLAYER1_SPEED 20

typedef struct Player1Property{
    int x,y; //位置
    int size;
    int hp_max;
}Player1Property;


typedef struct Player1{
    volatile Info info;
    volatile Player1Property property;
    Hp *hp;
}Player1;

typedef struct Player1_factory{
    Player1 __player1s[PLAYER1_MAX];
    int idx;
}Player1_factory;


Player1 *build_player1();

//*******************virtual functions***********************

//绘制
void player1_draw(Player1* );

//移动
void player1_move(Player1*,int,int);

//删除
void player1_delete(Player1* );

//
void player1_locate(Player1 *, UTIL_RECT*);

//
void player1_automove(Player1* player1);

//
void player1_answer(Player1*, int keycode);

//
void player1_hurt(Player1*, int);


#endif
