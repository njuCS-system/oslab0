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

    _Device *dev = getdev(&video_dev, _DEV_VIDEO);
    dev->write(_DEVREG_VIDEO_FBCTL, &ctl, sizeof(_FBCtlReg));
    draw_sync();

    fb_add(&ctl);
}


void planeU_move(PlaneU* planeU,int deltaU, int deltaY){
    planeU->property.x += deltaX;
    planeU->property.y += deltaY;
}

void planeU_automove(PlaneU* planeU){
    planeU->property.x += planeU->property.vx;
    planeU->property.y += planeU->property.vy;
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
}


//*****************************
//destructors
//*****************************
static void __finalize_PlaneU(PlaneU* planeU){
    //善后事宜
}