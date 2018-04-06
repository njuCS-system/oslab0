#include "bullet.h"


Bullet_factory bullet_factory;


static Bullet* bullet_allocate();

static void __init__Bullet(Bullet* bullet,BulletProperty property);

static void __finalize_Bullet(Bullet* bullet);

//*****************************
//构造器(们)无法多态
//****************************
Bullet* build_bullet(BulletProperty property){
    //mem_alloc 
    Bullet* bullet = bullet_allocate();
    //constructor
    if(bullet != NULL){
        __init__Bullet(bullet, property);

    }else{
        printf("[ERROR] Memory-allocate error when build a bullet!\n");
    }
    return bullet;
}



//***********************virtual functions**************************

void bullet_delete(Bullet* bullet){
    //destructor
    __finalize_Bullet(bullet);
    //free memory
    bullet->info.valid=FALSE;
}

void bullet_draw(Bullet* bullet){
    _FBCtlReg ctl;
    int x = bullet->property.x;
    int y = bullet->property.y;
    int size = bullet->property.size;
    
    CircleProperty p = {x, y, 3 * size, {31, 145, 249, 0}};
    bullet->body = build_circle(p);
    circle_draw(bullet->body);

    fb_add(&ctl);
}


void bullet_move(Bullet* bullet,int deltaX, int deltaY){
    bullet->property.x += deltaX;
    bullet->property.y += deltaY;
}

void bullet_automove(Bullet* bullet){
    bullet->property.x += bullet->property.vx;
    bullet->property.y += bullet->property.vy;
}



//****************************************************************

static Bullet* bullet_allocate(){
    Bullet* bullet;
    for(int i=0;i<BULLET_MAX;i++){
        bullet=&(bullet_factory.__bullets[bullet_factory.idx]);

        bullet_factory.idx++;
        bullet_factory.idx%=BULLET_MAX;

        if(!bullet->info.valid){//遇到有效的则返回
            bullet->info.valid=TRUE;
            return bullet;
        }
    }
    return NULL;
}

static void __init__Bullet(Bullet* bullet,BulletProperty property){
    //初始化逻辑
    bullet->info.type = 'B';
    bullet->info.valid = TRUE;
    bullet->property = property;
}


//*****************************
//destructors
//*****************************
static void __finalize_Bullet(Bullet* bullet){
    //善后事宜
    circle_delete(bullet->body);
}
