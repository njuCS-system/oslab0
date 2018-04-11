#include "hp.h"


Hp_factory hp_factory;


static Hp* hp_allocate();

static void __init__Hp(Hp* hp,HpProperty property);

static void __finalize_Hp(Hp* hp);

//*****************************
//构造器(们)无法多态
//****************************
Hp* build_hp(HpProperty property){
    //mem_alloc 
    Hp* hp = hp_allocate();
    //constructor
    if(hp!=NULL){
        __init__Hp(hp,property);

    }else{
        printf("[ERROR] Memory-allocate error when build a hp!\n");
    }
    return hp;
}



//***********************virtual functions**************************

void hp_delete(Hp* hp){
    //destructor
    __finalize_Hp(hp);
    //free memory
    hp->info.valid=FALSE;
}

void hp_draw(Hp* hp)
{
    const int offset = 10;
    int size = hp->property.size;
    int x = hp->property.x;
    int y;
    if(hp->property.is_player)
    {
        y = hp->property.y + PLANE_HEIGHT + offset;
    }
    else
    {
        y = hp->property.y - offset;
    }
    //                x    y                  w                                   h     s_color          f_color  stroke is_fill
    RectProperty p0 = {x, y, (30 * hp->hp_left) / hp->property.hp_max * size, 4 * size, {0, 255, 0, 0}, {0, 255, 0, 0}, 0, TRUE};
    Rect *left = build_rect(p0);
    RectProperty p1 = {x, y, 30 * size, 4 * size, {0, 255, 0, 0}, {0, 255, 0, 0}, 1, FALSE};
    Rect *lost = build_rect(p1);
    //rect_draw(lost);
    rect_draw(left);
    rect_delete(left);
    rect_delete(lost);
}


void hp_move(Hp* hp,int deltaX, int deltaY){
    hp->property.x += deltaX;
    hp->property.y += deltaY;
}

void hp_decrease(Hp* hp, int hp_lost)
{
    hp->hp_left -= hp_lost;
    if(hp->hp_left < 0)
    {
        hp->hp_left = 0;
    }
}


//****************************************************************

static Hp* hp_allocate(){
    Hp* hp;
    for(int i=0;i<HP_MAX;i++){
        hp=&(hp_factory.__hps[hp_factory.idx]);

        hp_factory.idx++;
        hp_factory.idx%=HP_MAX;

        if(!hp->info.valid){//遇到有效的则返回
            hp->info.valid=TRUE;
            return hp;
        }
    }
    return NULL;
}

static void __init__Hp(Hp* hp,HpProperty property){
    //初始化逻辑
    hp->info.type = 'h';
    hp->info.valid = TRUE;
    hp->property = property;
    hp->hp_left = hp->property.hp_max;
}


//*****************************
//destructors
//*****************************
static void __finalize_Hp(Hp* hp){
    //善后事宜
}
