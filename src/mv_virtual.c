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
    }

}
