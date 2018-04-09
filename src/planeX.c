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
    _FBCtlReg ctl;

    BITMAPINFOHEADER *bmpHead = (BITMAPINFOHEADER*) (model_planeX + BITMAPFILEHEADER_LENGTH);
    printf("%d\n", sizeof(BITMAPFILEHEADER));
    long width = bmpHead -> biWidth;
    long height = bmpHead -> biHeight;
    printf("%d %d\n", width, height);

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

    _Device *dev = getdev(&video_dev, _DEV_VIDEO);
    dev->write(_DEVREG_VIDEO_FBCTL, &ctl, sizeof(_FBCtlReg));
    draw_sync();

    fb_add(&ctl);
}


void planeX_move(PlaneX* planeX,int deltaX, int deltaY){
    planeX->property.x += deltaX;
    planeX->property.y += deltaY;
}

void planeX_automove(PlaneX* planeX){
    planeX->property.x += planeX->property.vx;
    planeX->property.y += planeX->property.vy;
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
}


//*****************************
//destructors
//*****************************
static void __finalize_PlaneX(PlaneX* planeX){
    //善后事宜
    rect_delete(planeX->large_wing);
    rect_delete(planeX->small_wing);
    rect_delete(planeX->empennage_left);
    rect_delete(planeX->empennage_right);
    rect_delete(planeX->body);
    rect_delete(planeX->jet_left);
    rect_delete(planeX->jet_right);
}
