#include "memory.h"
#include "component.h"

Rect_factory rect_factory;

Rect* build_rect(RectProperty property){
    return __init_build_rect(&rect_factory,property);
}


Rect* __init_build_rect(Rect_factory * factory,RectProperty property){
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

void init_memory(){
    rect_factory.build=&build_rect;
}
