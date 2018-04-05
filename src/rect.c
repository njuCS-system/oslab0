#include "rect.h"


Rect_factory rect_factory;


static Rect* rect_allocate();

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
        // printf("[ERROR] Memory-allocate error when build a rectangle!");
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

void rect_draw(Rect* rect){
    //TODO:
}


void rect_move(Rect* rect,int deltaX, int deltaY){
    //TODO:
}



//****************************************************************

static Rect* rect_allocate(){
    Rect* rect;
    for(int i=0;i<RECT_MAX;i++){
        rect=&(rect_factory.__rects[rect_factory.idx]);

        rect_factory.idx++;
        rect_factory.idx%=RECT_MAX;
        
        if(rect->info.valid){//遇到有效的则返回
            rect->info.valid=TRUE;
            return rect;
        }
    }
    return NULL;
}

static void __init__Rect(Rect* rect,RectProperty property){
    //矩形初始化逻辑
}


//*****************************
//destructors
//*****************************
static void __finalize_Rect(Rect* rect){
    //矩形的善后事宜
}