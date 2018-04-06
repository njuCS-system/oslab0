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
    
    //                x    y     w   h     s_color        f_color  stroke is_fill
    RectProperty p0 = {x, y + 16, 30, 6, {0, 0, 0, 0}, {255, 0, 0, 0}, 1, TRUE};
    Rect *large_wing = build_rect(p0);
    RectProperty p1 = {x + 9, y + 2, 12, 2, {0, 0, 0, 0}, {255, 0, 0, 0}, 1, TRUE};
    Rect *small_wing = build_rect(p1);
    RectProperty p2 = {x + 10, y, 2, 6, {0, 0, 0, 0}, {43, 244, 249, 0}, 1, TRUE};
    Rect *empennage_left = build_rect(p2);
    RectProperty p3 = {x + 18, y, 2, 6, {0, 0, 0, 0}, {43, 244, 249, 0}, 1, TRUE};
    Rect *empennage_right = build_rect(p3);
    RectProperty p4 = {x + 13, y + 2, 4, 25, {0, 0, 0, 0}, {71, 173, 112, 0}, 1, TRUE};
    Rect *body = build_rect(p4);
    RectProperty p5 = {x + 5, y + 15, 3, 9, {0, 0, 0, 0}, {43, 244, 249, 0}, 1, TRUE};
    Rect *jet_left = build_rect(p5);
    RectProperty p6 = {x + 22, y + 15, 3, 9, {0, 0, 0, 0}, {43, 244, 249, 0}, 1, TRUE};
    Rect *jet_right = build_rect(p6);
    
    rect_draw(large_wing);
    rect_draw(small_wing);
    rect_draw(empennage_left);
    rect_draw(empennage_right);
    //rect_draw(body);
    rect_draw(jet_left);
    rect_draw(jet_right);
    /*_Device *dev = getdev(&video_dev, _DEV_VIDEO);
    dev->write(_DEVREG_VIDEO_FBCTL, &ctl, sizeof(_FBCtlReg));
    draw_sync();*/
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
