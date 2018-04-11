#include "battle_virtual.h"

void battle_virtual_hurt(void* obj, int hp_lost){
    Info info = *((Info*)obj);
    if(!info.valid){
        return;
    }
    
    switch(info.type){
        case 'I':
            planeI_hurt((PlaneI *)obj, hp_lost);
            break;
        case 'T':
            planeT_hurt((PlaneT *)obj, hp_lost);
            break;
        case 'U':
            planeU_hurt((PlaneU *)obj, hp_lost);
            break;
        case 'X':
            planeX_hurt((PlaneX *)obj, hp_lost);
            break;
        case 'P':
            player1_hurt((Player1 *)obj, hp_lost);
            break;
    }
}

bool battle_virtual_isCrash(void *obj)
{
    Info info = *((Info*)obj);
    if(!info.valid){
        return false;
    }
    
    switch(info.type){
        case 'I':
            return planeI_isCrash((PlaneI *)obj);
            break;
        case 'T':
            return planeT_isCrash((PlaneT *)obj);
            break;
        case 'U':
            return planeU_isCrash((PlaneU *)obj);
            break;
        case 'X':
            return planeX_isCrash((PlaneX *)obj);
            break;
        case 'P':
            return planeP_isCrash((PlaneP *)obj);
            break;
    }

    return false;
}
