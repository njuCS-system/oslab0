#include "planeT.h"


PlaneT_factory planeT_factory;


static PlaneT* planeT_allocate();

static void __init__PlaneT(PlaneT* planeT,PlaneTProperty property);

static void __finalize_PlaneT(PlaneT* planeT);

//*****************************
//构造器(们)无法多态
//****************************
PlaneT* build_planeT(PlaneTProperty property){
    //mem_alloc 
    PlaneT* planeT = planeT_allocate();
    //constructor
    if(planeT!=NULL){
        __init__PlaneT(planeT,property);

    }else{
        printf("[ERROR] Memory-allocate error when build a planeT!\n");
    }
    return planeT;
}



//***********************virtual functions**************************

void planeT_delete(PlaneT* planeT){
    //destructor
    __finalize_PlaneT(planeT);
    //free memory
    planeT->info.valid=FALSE;
}

void planeT_draw(PlaneT* planeT){
    hp_draw(planeT->hp);
    _FBCtlReg ctl;

    BITMAPINFOHEADER *bmpHead = (BITMAPINFOHEADER*) (model_planeT + BITMAPFILEHEADER_LENGTH);
    long width = bmpHead -> biWidth;
    long height = bmpHead -> biHeight;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            Color temp_color;
            temp_color.b = bmpHead -> pixels[(i * width + j) * 3];
            temp_color.g = bmpHead -> pixels[(i * width + j) * 3 + 1];
            temp_color.r = bmpHead -> pixels[(i * width + j) * 3 + 2];
            if(temp_color.b == 1 && temp_color.g == 1 && temp_color.r == 1)
            {
                temp_color.a = 1;
            }
            else
            {
                temp_color.a = 0;
            }
            color_buf[i * width + j] = color_to_int(temp_color);
        }
    }
    
    ctl.x = planeT->property.x;
    ctl.y = planeT->property.y;
    ctl.pixels = color_buf;
    ctl.w = width;
    ctl.h = height;
    ctl.sync = 0;

    /*video_draw(ctl);
    draw_sync();*/

    fb_add(&ctl);
}


void planeT_move(PlaneT* planeT,int deltaX, int deltaY){
    planeT->property.x += deltaX;
    planeT->property.y += deltaY;
    hp_move(planeT->hp, deltaX, deltaY);
}

void planeT_locate(PlaneT *planeT, UTIL_RECT *ur)
{
    ur->x = planeT->property.x;
    ur->y = planeT->property.y;
    BITMAPINFOHEADER *bmpHead = (BITMAPINFOHEADER*) (model_planeT + BITMAPFILEHEADER_LENGTH);
    ur->w = bmpHead -> biWidth;
    ur->h = bmpHead -> biHeight;
}

void planeT_automove(PlaneT* planeT){
    planeT->property.x += planeT->property.vx;
    planeT->property.y += planeT->property.vy;
    hp_move(planeT->hp, planeT->property.vx, planeT->property.vy);
}

void planeT_hurt(PlaneT *planeT, int hp_lost)
{
    hp_decrease(planeT->hp, hp_lost);
}

bool planeT_isCrash(PlaneT *planeT)
{
    return planeT->hp->hp_left <= 0;
}

int planeT_get_attack(PlaneT *planeT)
{
    return planeT->property.attack;
}

void planeT_set_attack(PlaneT *planeT, int attack)
{
    planeT->property.attack = attack;
}

int planeT_get_hp(PlaneT *planeT)
{
    return planeT->hp->hp_left;
}

//****************************************************************

static PlaneT* planeT_allocate(){
    PlaneT* planeT;
    for(int i=0;i<PLANET_MAX;i++){
        planeT=&(planeT_factory.__planeTs[planeT_factory.idx]);

        planeT_factory.idx++;
        planeT_factory.idx%=PLANET_MAX;

        if(!planeT->info.valid){//遇到有效的则返回
            planeT->info.valid=TRUE;
            return planeT;
        }
    }
    return NULL;
}

static void __init__PlaneT(PlaneT* planeT,PlaneTProperty property){
    //初始化逻辑
    planeT->info.type = 'T';
    planeT->info.valid = TRUE;
    planeT->property = property;

    int x = planeT->property.x;
    int y = planeT->property.y;
    HpProperty h = {x, y, 2, planeT->property.hp_max, FALSE};
    planeT->hp = build_hp(h);
}


//*****************************
//destructors
//*****************************
static void __finalize_PlaneT(PlaneT* planeT){
    //善后事宜
    hp_delete(planeT->hp);
}
