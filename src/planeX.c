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
    int x = planeX->property.x;
    int y = planeX->property.y;
    int size = planeX->property.size;
    
    //                x    y     w   h     s_color        f_color  stroke is_fill
    RectProperty p0 = {x, y + 16 * size, 30 * size, 6 * size, {0, 0, 0, 0}, {49, 125, 237, 0}, 1, TRUE};
    planeX->large_wing = build_rect(p0);
    RectProperty p1 = {x + 8 * size, y + 2 * size, 14 * size, 3 * size, {0, 0, 0, 0}, {49, 125, 237, 0}, 1, TRUE};
    planeX->small_wing = build_rect(p1);
    RectProperty p2 = {x + 9 * size, y, 3 * size, 6 * size, {0, 0, 0, 0}, {240, 176, 0, 0}, 1, TRUE};
    planeX->empennage_left = build_rect(p2);
    RectProperty p3 = {x + 18 * size, y, 3 * size, 6 * size, {0, 0, 0, 0}, {240, 176, 0, 0}, 1, TRUE};
    planeX->empennage_right = build_rect(p3);
    RectProperty p4 = {x + 13 * size, y + 2 * size, 4 * size, 14 * size, {0, 0, 0, 0}, {71, 173, 112, 0}, 1, TRUE};
    planeX->body = build_rect(p4);
    RectProperty p5 = {x + 5 * size, y + 15 * size, 3 * size, 9 * size, {0, 0, 0, 0}, {240, 176, 0, 0}, 1, TRUE};
    planeX->jet_left = build_rect(p5);
    RectProperty p6 = {x + 22 * size, y + 15 * size, 3 * size, 9 * size, {0, 0, 0, 0}, {240, 176, 0, 0}, 1, TRUE};
    planeX->jet_right = build_rect(p6);
    
    rect_draw(planeX->large_wing);
    rect_draw(planeX->small_wing);
    rect_draw(planeX->empennage_left);
    rect_draw(planeX->empennage_right);
    rect_draw(planeX->body);
    rect_draw(planeX->jet_left);
    rect_draw(planeX->jet_right);
    /*_Device *dev = getdev(&video_dev, _DEV_VIDEO);
    dev->write(_DEVREG_VIDEO_FBCTL, &ctl, sizeof(_FBCtlReg));
    draw_sync();*/
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
