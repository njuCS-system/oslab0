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

static _Device *getdev(_Device **ptr, uint32_t id) {
  if (*ptr) return *ptr;
  for (int n = 1; ; n ++) {
    _Device *cur = _device(n);
    if (cur->id == id) {
      *ptr = cur;
      return cur;
    }
    if (!cur) break;
  }
  //assert(0);
  return NULL;
}
static _Device *video_dev;

void circle_draw(Circle* circle){
    _FBCtlReg ctl;
    //unsigned color = color_to_int(circle->property.color);
    //unsigned color_buf[_WIDTH * _HEIGHT];
    
    
    
    //_Device *dev = getdev(&video_dev, _DEV_VIDEO);
    //dev->write(_DEVREG_VIDEO_FBCTL, &ctl, sizeof(_FBCtlReg));
    //draw_sync();
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
    //矩形初始化逻辑
    circle->info.type = 'C';
    circle->info.valid = TRUE;
    circle->property = property;
}


//*****************************
//destructors
//*****************************
static void __finalize_Circle(Circle* circle){
    //矩形的善后事宜
}
