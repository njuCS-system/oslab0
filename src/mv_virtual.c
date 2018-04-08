#include "mv_virtual.h"

void mv_virtual_automove(void* obj){
    Info info = *((Info*)obj);
    if(!info.valid){
        return;
    }
    
    switch(info.type){
        case 'I':
            planeI_automove((PlaneI*)obj);
            break;
        case 'X':
            planeX_automove((PlaneX*)obj);
            break;
        case 'B':
            bullet_automove((Bullet*)obj);
            break;
    }
}
