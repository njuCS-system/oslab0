#include "cp_virtual.h"

void cp_virtual_draw(void* obj){
    Info info = *((Info*)obj);
    if(!info.valid){
        return;
    }
    
    switch(info.type){
        case 'R':
            rect_draw((Rect*)obj);
            break;

        case 'C':
            circle_draw((Circle *)obj);
            break;
    }

}

void cp_virtual_delete(void* obj){
    Info info = *((Info*)obj);
    if(!info.valid){
        return;
    }
    
    switch(info.type){
        case 'R':
            rect_delete((Rect*)obj);
            break;

        case 'C':
            circle_delete((Circle *)obj);
            break;
    }
}


void cp_virtual_move(void* obj,int deltaX, int deltaY){
}
