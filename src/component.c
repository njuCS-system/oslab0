#include "component.h"


//****************************
//constructors
//****************************
void __init__Rect(Rect* rect,RectProperty property){
    //矩形初始化逻辑
}


//*****************************
//destructors
//*****************************
void __finalize_Rect(Rect* rect){
    //矩形的善后事宜
}









//***************************
//virtual functions
//****************************
static void draw_rect(Rect* rect){
    //矩形绘制逻辑
}
void draw(void* obj){
    Info info=((Info*)obj)[0];
    if(!info.valid.boolean){
        return NULL;
    }
    
    switch(info.type){
        case 'R':
            draw_rect((Rect*)obj);
            break;
        
    }

}