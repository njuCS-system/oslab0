#include "rect.h"


Rect_factory rect_factory;


static Rect* rect_allocate();

static void __init__Rect(Rect* rect,RectProperty property);

static void __finalize_Rect(Rect* rect);

//*****************************
//构造器(们)无法多态
//****************************
Rect* build_rect(RectProperty property){
    //mem_alloc 
    Rect* rect= rect_allocate();
    //constructor
    if(rect!=NULL){
        __init__Rect(rect,property);

    }else{
        printf("[ERROR] Memory-allocate error when build a rectangle!\n");
    }
    return rect;
}



//***********************virtual functions**************************

void rect_delete(Rect* rect){
    //destructor
    __finalize_Rect(rect);
    //free memory
    rect->info.valid=FALSE;
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

void draw_sync() {
  _Device *dev = getdev(&video_dev, _DEV_VIDEO);
  _FBCtlReg ctl;
  ctl.pixels = NULL;
  ctl.x = ctl.y = ctl.w = ctl.h = 0;
  ctl.sync = 1;
  dev->write(_DEVREG_VIDEO_FBCTL, &ctl, sizeof(ctl));
}

void rect_draw(Rect* rect){
    _FBCtlReg ctl;
    unsigned s_color = color_to_int(rect->property.s_color);
    unsigned f_color = color_to_int(rect->property.f_color);
    
    //printf("%d\n", HEIGHT);
    unsigned color_buf[50];
    //memset(color_buf, 0 ,sizeof(int) * WIDTH * HEIGHT);
    //printf("hello1\n");
    //printf("%d %d\n", rect->property.height, rect->property.width);
    for(int i = 0; i < rect->property.height; i++)
    {
    	for(int j = 0; j < rect->property.width; j++)
        {
            if(i < rect->property.stroke || j < rect->property.stroke 
            || i + rect->property.stroke >= rect->property.height || j + rect->property.stroke >= rect->property.width)
            {
                color_buf[i * rect->property.width + j] = s_color;
            }
            else
            {
                if(rect->property.is_fill)
                {
                    color_buf[i * rect->property.width + j] = f_color;
                }
                else
                {
                    color_buf[i * rect->property.width + j] = DEFAULT_COLOR;
                }
            }
        }
    }
    ctl.x = rect->property.x;
    ctl.y = rect->property.y;
    ctl.pixels = color_buf;
    ctl.w = rect->property.width;
    ctl.h = rect->property.height;
    ctl.sync = 0;
    
    //printf("%d %d %d %d\n", ctl.x, ctl.y, ctl.w, ctl.h);
    
    _Device *dev = getdev(&video_dev, _DEV_VIDEO);
    dev->write(_DEVREG_VIDEO_FBCTL, &ctl, sizeof(_FBCtlReg));
    draw_sync();
    fb_add(&ctl);
}


void rect_move(Rect* rect,int deltaX, int deltaY){
    rect->property.x += deltaX;
    rect->property.y += deltaY;
}



//****************************************************************

static Rect* rect_allocate(){
    Rect* rect;
    for(int i=0;i<RECT_MAX;i++){
        rect=&(rect_factory.__rects[rect_factory.idx]);

        rect_factory.idx++;
        rect_factory.idx%=RECT_MAX;

        if(!rect->info.valid){//遇到有效的则返回
            rect->info.valid=TRUE;
            return rect;
        }
    }
    return NULL;
}

static void __init__Rect(Rect* rect,RectProperty property){
    //矩形初始化逻辑
    rect->info.type = 'R';
    rect->info.valid = TRUE;
    rect->property = property;
}


//*****************************
//destructors
//*****************************
static void __finalize_Rect(Rect* rect){
    //矩形的善后事宜
}
