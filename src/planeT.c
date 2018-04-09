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

    _Device *dev = getdev(&video_dev, _DEV_VIDEO);
    dev->write(_DEVREG_VIDEO_FBCTL, &ctl, sizeof(_FBCtlReg));
    draw_sync();

    fb_add(&ctl);
}


void planeT_move(PlaneT* planeT,int deltaX, int deltaY){
    planeT->property.x += deltaX;
    planeT->property.y += deltaY;
}

void planeT_automove(PlaneT* planeT){
    planeT->property.x += planeT->property.vx;
    planeT->property.y += planeT->property.vy;
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
}


//*****************************
//destructors
//*****************************
static void __finalize_PlaneT(PlaneT* planeT){
    //善后事宜
}
