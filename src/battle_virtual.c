#include "battle_virtual.h"

void battle_virtual_hurt(void* obj, int hp_lost){
    Info info = *((Info*)obj);
    if(!info.valid){
        return;
    }
    
    switch(info.type){
        case 'I':
            planeI_hurt((PlaneI *)obj, hp_lost);
        case 'T':
            planeT_hurt((PlaneT *)obj, hp_lost);
        case 'U':
            planeU_hurt((PlaneU *)obj, hp_lost);
        case 'X':
            planeX_hurt((PlaneX *)obj, hp_lost);
        case 'P':
            player1_hurt((Player1 *)obj, hp_lost);
    }
}
