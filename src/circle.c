#include "circle.h"


Circle_factory circle_factory;


static Circle* circle_allocate();

static void __init__Circle(Circle* circle,CircleProperty property);

static void __finalize_Circle(Circle* circle);

//*****************************
//构造器(们)无法多态
//****************************
Circle* build_circle(CircleProperty property){
    //mem_alloc 
    Circle* circle = circle_allocate();
    //constructor
    if(circle!=NULL){
        __init__Circle(circle,property);

    }else{
        printf("[ERROR] Memory-allocate error when build a circle!\n");
    }
    return circle;
}



//***********************virtual functions**************************

void circle_delete(Circle* circle){
    //destructor
    __finalize_Circle(circle);
    //free memory
    circle->info.valid=FALSE;
}

void circle_draw(Circle* circle){
    _FBCtlReg ctl;
    unsigned color = color_to_int(circle->property.color);
    int r = circle->property.r;
    int r_square = r * r;
    
    ctl.x = circle->property.x - r;
    ctl.y = circle->property.y - r;
    ctl.w = 2 * r;
    ctl.h = 2 * r;
    
    for(int i = 0; i < r * 2; i++)
    {
        for(int j = 0; j < r * 2; j++)
        {
            if((i - r) * (i - r) + (j - r) * (j - r) <= r_square)
            {
                color_buf[i * 2 * r + j] = color;
            }
            else
            {
                color_buf[i * 2 * r + j] = DEFAULT_COLOR;
            }
        }
    }
    
    ctl.pixels = color_buf;
    
    _Device *dev = getdev(&video_dev, _DEV_VIDEO);
    dev->write(_DEVREG_VIDEO_FBCTL, &ctl, sizeof(_FBCtlReg));
    draw_sync();
    fb_add(&ctl);
}


void circle_move(Circle* circle,int deltaX, int deltaY){
    circle->property.x += deltaX;
    circle->property.y += deltaY;
}



//****************************************************************

static Circle* circle_allocate(){
    Circle* circle;
    for(int i=0;i<CIRCLE_MAX;i++){
        circle=&(circle_factory.__circles[circle_factory.idx]);

        circle_factory.idx++;
        circle_factory.idx%=CIRCLE_MAX;

        if(!circle->info.valid){//遇到有效的则返回
            circle->info.valid=TRUE;
            return circle;
        }
    }
    return NULL;
}

static void __init__Circle(Circle* circle,CircleProperty property){
    //初始化逻辑
    circle->info.type = 'C';
    circle->info.valid = TRUE;
    circle->property = property;
}


//*****************************
//destructors
//*****************************
static void __finalize_Circle(Circle* circle){
    //善后事宜
}
