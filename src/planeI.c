#include "planeI.h"


PlaneI_factory planeI_factory;


static PlaneI* planeI_allocate();

static void __init__PlaneI(PlaneI* planeI,PlaneIProperty property);

static void __finalize_PlaneI(PlaneI* planeI);

//*****************************
//构造器(们)无法多态
//****************************
PlaneI* build_planeI(PlaneIProperty property){
    //mem_alloc 
    PlaneI* planeI = planeI_allocate();
    //constructor
    if(planeI!=NULL){
        __init__PlaneI(planeI,property);

    }else{
        printf("[ERROR] Memory-allocate error when build a planeI!\n");
    }
    return planeI;
}



//***********************virtual functions**************************

void planeI_delete(PlaneI* planeI){
    //destructor
    __finalize_PlaneI(planeI);
    //free memory
    planeI->info.valid=FALSE;
}

void planeI_draw(PlaneI* planeI){
    _FBCtlReg ctl;
    int x = planeI->property.x;
    int y = planeI->property.y;
    
    //                x       y  w   h     s_color        f_color  stroke is_fill
    /*RectProperty p = {x, y + 16, 30, 6, {0, 0, 0, 0}, {255, 0, 0, 0}, 1, TRUE};
    Rect* large_wing = build_rect(p);
                 p = {x + 16, y, 30, 6, {0, 0, 0, 0}, {255, 0, 0, 0}, 1, TRUE};
    Rect* small_wing = build_rect(p);
*/
    _Device *dev = getdev(&video_dev, _DEV_VIDEO);
    dev->write(_DEVREG_VIDEO_FBCTL, &ctl, sizeof(_FBCtlReg));
    draw_sync();
    fb_add(&ctl);
}


void planeI_move(PlaneI* planeI,int deltaX, int deltaY){
    planeI->property.x += deltaX;
    planeI->property.y += deltaY;
}

void planeI_automove(PlaneI* planeI){
    planeI->property.x += planeI->property.vx;
    planeI->property.y += planeI->property.vy;
}



//****************************************************************

static PlaneI* planeI_allocate(){
    PlaneI* planeI;
    for(int i=0;i<PLANEI_MAX;i++){
        planeI=&(planeI_factory.__planeIs[planeI_factory.idx]);

        planeI_factory.idx++;
        planeI_factory.idx%=PLANEI_MAX;

        if(!planeI->info.valid){//遇到有效的则返回
            planeI->info.valid=TRUE;
            return planeI;
        }
    }
    return NULL;
}

static void __init__PlaneI(PlaneI* planeI,PlaneIProperty property){
    //初始化逻辑
    planeI->info.type = 'I';
    planeI->info.valid = TRUE;
    planeI->property = property;
}


//*****************************
//destructors
//*****************************
static void __finalize_PlaneI(PlaneI* planeI){
    //善后事宜
}
