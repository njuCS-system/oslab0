#ifndef BIGEXPLOSION3_H
#define BIGEXPLOSION3_H

#include "util.h"
#include "rect.h"


#define BIGEXPLOSION_MAX 20


typedef struct BigExplosion3Property{
    int x,y; //位置
    int vx, vy;
    int size;
}BigExplosion3Property;


typedef struct BigExplosion3{
    volatile Info info;
    volatile BigExplosion3Property property;
}BigExplosion3;

typedef struct BigExplosion3_factory{
    BigExplosion3 __bigExplosion3s[BIGEXPLOSION_MAX];
    int idx;
}BigExplosion3_factory;


BigExplosion3 *build_bigExplosion3();

//*******************virtual functions***********************

//绘制
void bigExplosion3_draw(BigExplosion3* );

//移动
void bigExplosion3_move(BigExplosion3*,int,int);

//删除
void bigExplosion3_delete(BigExplosion3* );

//
void bigExplosion3_automove(BigExplosion3* bigExplosion3);




#endif
