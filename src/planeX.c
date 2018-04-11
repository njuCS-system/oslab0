#include "planeX.h"


PlaneX_factory planeX_factory;


static PlaneX* planeX_allocate();

static void __init__PlaneX(PlaneX* planeX,PlaneXProperty property);

static void __finalize_PlaneX(PlaneX* planeX);

//*****************************
//构造器(们)无法多态
//****************************
PlaneX* build_planeX(PlaneXProperty property){
    //mem_alloc 
    PlaneX* planeX = planeX_allocate();
    //constructor
    if(planeX!=NULL){
        __init__PlaneX(planeX,property);

    }else{
        printf("[ERROR] Memory-allocate error when build a planeX!\n");
    }
    return planeX;
}



//***********************virtual functions**************************

void planeX_delete(PlaneX* planeX){
    //destructor
    __finalize_PlaneX(planeX);
    //free memory
    planeX->info.valid=FALSE;
}

void planeX_draw(PlaneX* planeX){
    hp_draw(planeX->hp);
    _FBCtlReg ctl;

    BITMAPINFOHEADER *bmpHead = (BITMAPINFOHEADER*) (model_planeX + BITMAPFILEHEADER_LENGTH);
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
    
    ctl.x = planeX->property.x;
    ctl.y = planeX->property.y;
    ctl.pixels = color_buf;
    ctl.w = width;
    ctl.h = height;
    ctl.sync = 0;

    // video_draw(ctl);
    // draw_sync();

    fb_add(&ctl);
}


void planeX_move(PlaneX* planeX,int deltaX, int deltaY){
    planeX->property.x += deltaX;
    planeX->property.y += deltaY;
    hp_move(planeX->hp, deltaX, deltaY);
}

void planeX_locate(PlaneX *planeX, UTIL_RECT *ur)
{
    ur->x = planeX->property.x;
    ur->y = planeX->property.y;
    BITMAPINFOHEADER *bmpHead = (BITMAPINFOHEADER*) (model_planeX + BITMAPFILEHEADER_LENGTH);
    ur->w = bmpHead -> biWidth;
    ur->h = bmpHead -> biHeight;
}

void planeX_automove(PlaneX* planeX){
    planeX->property.x += planeX->property.vx;
    planeX->property.y += planeX->property.vy;
    hp_move(planeX->hp, planeX->property.vx, planeX->property.vy);
}

void planeX_hurt(PlaneX *planeX, int hp_lost)
{
    hp_decrease(planeX->hp, hp_lost);
}

bool planeX_isCrash(PlaneX *planeX)
{
    return planeX->hp->hp_left <= 0;
}

//****************************************************************

static PlaneX* planeX_allocate(){
    PlaneX* planeX;
    for(int i=0;i<PLANEX_MAX;i++){
        planeX=&(planeX_factory.__planeXs[planeX_factory.idx]);

        planeX_factory.idx++;
        planeX_factory.idx%=PLANEX_MAX;

        if(!planeX->info.valid){//遇到有效的则返回
            planeX->info.valid=TRUE;
            return planeX;
        }
    }
    return NULL;
}

static void __init__PlaneX(PlaneX* planeX,PlaneXProperty property){
    //初始化逻辑
    planeX->info.type = 'X';
    planeX->info.valid = TRUE;
    planeX->property = property;

    int x = planeX->property.x;
    int y = planeX->property.y;
    HpProperty h = {x, y, 2, planeX->property.hp_max, FALSE};
    planeX->hp = build_hp(h);
}


//*****************************
//destructors
//*****************************
static void __finalize_PlaneX(PlaneX* planeX){
    //善后事宜
    hp_delete(planeX->hp);
}
