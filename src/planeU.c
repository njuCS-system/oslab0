#include "planeU.h"


PlaneU_factory planeU_factory;


static PlaneU* planeU_allocate();

static void __init__PlaneU(PlaneU* planeU,PlaneUProperty property);

static void __finalize_PlaneU(PlaneU* planeU);

//*****************************
//构造器(们)无法多态
//****************************
PlaneU* build_planeU(PlaneUProperty property){
    //mem_alloc 
    PlaneU* planeU = planeU_allocate();
    //constructor
    if(planeU!=NULL){
        __init__PlaneU(planeU,property);

    }else{
        printf("[ERROR] Memory-allocate error when build a planeU!\n");
    }
    return planeU;
}



//***********************virtual functions**************************

void planeU_delete(PlaneU* planeU){
    //destructor
    __finalize_PlaneU(planeU);
    //free memory
    planeU->info.valid=FALSE;
}

void planeU_draw(PlaneU* planeU){
    _FBCtlReg ctl;

    BITMAPINFOHEADER *bmpHead = (BITMAPINFOHEADER*) (model_planeU + BITMAPFILEHEADER_LENGTH);
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
    
    ctl.x = planeU->property.x;
    ctl.y = planeU->property.y;
    ctl.pixels = color_buf;
    ctl.w = width;
    ctl.h = height;
    ctl.sync = 0;

    video_draw(ctl);
    draw_sync();

    hp_draw(planeU->hp);
    fb_add(&ctl);
}


void planeU_move(PlaneU* planeU,int deltaX, int deltaY){
    planeU->property.x += deltaX;
    planeU->property.y += deltaY;
    hp_move(planeU->hp, deltaX, deltaY);
}

void planeU_automove(PlaneU* planeU){
    planeU->property.x += planeU->property.vx;
    planeU->property.y += planeU->property.vy;
    hp_move(planeU->hp, planeU->property.vx, planeU->property.vy);
}

void planeU_hurt(PlaneU *planeU, int hp_lost)
{
    printf("%d\n", hp_lost);
    hp_decrease(planeU->hp, hp_lost);
}

//****************************************************************

static PlaneU* planeU_allocate(){
    PlaneU* planeU;
    for(int i=0;i<PLANEU_MAX;i++){
        planeU=&(planeU_factory.__planeUs[planeU_factory.idx]);

        planeU_factory.idx++;
        planeU_factory.idx%=PLANEU_MAX;

        if(!planeU->info.valid){//遇到有效的则返回
            planeU->info.valid=TRUE;
            return planeU;
        }
    }
    return NULL;
}

static void __init__PlaneU(PlaneU* planeU,PlaneUProperty property){
    //初始化逻辑
    planeU->info.type = 'U';
    planeU->info.valid = TRUE;
    planeU->property = property;

    int x = planeU->property.x;
    int y = planeU->property.y;
    HpProperty h = {x, y, 2, planeU->property.hp_max, FALSE};
    planeU->hp = build_hp(h);
}


//*****************************
//destructors
//*****************************
static void __finalize_PlaneU(PlaneU* planeU){
    //善后事宜
    hp_delete(planeU->hp);
}
