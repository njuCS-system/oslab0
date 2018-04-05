#include "cp_virtual.h"

void cp_virtual_draw(void* obj){
    Info info=((Info*)obj)[0];
    if(!info.valid){
        return;
    }
    
    switch(info.type){
        case 'R':
            rect_draw((Rect*)obj);
            break;
        
    }

}

void cp_virtual_delete(void* obj){
}


void cp_virtual_move(void* obj,int deltaX, int deltaY){
}
