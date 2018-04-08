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
        case 'L':
            line_draw((Line *)obj);
            break;
        case 'I':
            planeI_draw((PlaneI *)obj);
            break;
        case 'X':
            planeX_draw((PlaneX *)obj);
            break;
        case 'B':
            bullet_draw((Bullet *)obj);
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
        case 'L':
            line_delete((Line *)obj);
            break;
        case 'I':
            planeI_delete((PlaneI *)obj);
            break;
        case 'X':
            planeX_delete((PlaneX *)obj);
            break;
        case 'B':
            bullet_delete((Bullet *)obj);
            break;
    }
}


void cp_virtual_move(void* obj,int deltaX, int deltaY){
    Info info = *((Info*)obj);
    if(!info.valid){
        return;
    }
    
    switch(info.type){
        case 'R':
            rect_move((Rect*)obj, deltaX, deltaY);
            break;
        case 'C':
            circle_move((Circle *)obj, deltaX, deltaY);
            break;
        case 'L':
            line_move((Line *)obj, deltaX, deltaY);
            break;
        case 'I':
            planeI_move((PlaneI *)obj, deltaX, deltaY);
            break;
        case 'X':
            planeX_delete((PlaneX *)obj);
            break;
        case 'B':
            bullet_move((Bullet *)obj, deltaX, deltaY);
            break;
    }
}
