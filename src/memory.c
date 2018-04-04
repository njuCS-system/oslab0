#include "memory.h"
#include "component.h"

Rect_factory rect_factory;
static Rect* __inner_build_rect(Rect_factory * factory);

//*****************************
//构造器(们)无法多态
//****************************
Rect* build_rect(RectProperty property){
    //mem_alloc 
    Rect* rect= __inner_build_rect(&rect_factory);
    //constructor
    if(rect!=NULL){
        __init__Rect(rect,property);

    }else{
        // printf("[ERROR] Memory-allocate error when build a rectangle!");
    }
    return rect;
}



static Rect* __inner_build_rect(Rect_factory * factory){
    Rect* rect;
    for(int i=0;i<RECT_MAX;i++){
        rect=&(factory->__rects[factory->idx]);

        factory->idx++;
        factory->idx%=RECT_MAX;
        
        if(rect->info.valid.boolean){//遇到有效的则返回，并将valid清空
            rect->info.valid.boolean=FALSE;
            return rect;
        }
    }
    return NULL;
}

static void free_rect(Rect* rect){
    //destructor
    __finalize_Rect(rect);
    //free memory
    rect->info.valid.boolean=TRUE;
}

void init_memory(){
    rect_factory.build=&build_rect;
    rect_factory.free=&free_rect;
}





//************************************
//virtual functions
//************************************

void free(void* obj){
    Info info=((Info*)obj)[0];
    if(!info.valid.boolean){
        return;
    }
    switch(info.type){
        case 'R':
            free_rect((Rect*)obj);
            break;

    }
}

