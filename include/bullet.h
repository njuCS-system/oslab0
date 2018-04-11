#ifndef BULLET_H
#define BULLET_H

#include "util.h"
#include "circle.h"


#define BULLET_MAX 100


typedef struct BulletProperty{
    int x,y; //位置
    int vx, vy;
    int size;
}BulletProperty;


typedef struct Bullet{
    volatile Info info;
    volatile BulletProperty property;
}Bullet;

typedef struct Bullet_factory{
    Bullet __bullets[BULLET_MAX];
    int idx;
}Bullet_factory;


Bullet *build_bullet();

//*******************virtual functions***********************

//绘制
void bullet_draw(Bullet* );

//移动
void bullet_move(Bullet*,int,int);

//删除
void bullet_delete(Bullet* );

//
void bullet_locate(Bullet *, UTIL_RECT*);

//
void bullet_automove(Bullet* bullet);




#endif
