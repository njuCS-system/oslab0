#include "battle_virtual.h"

void battle_virtual_hurt(void* obj, int hp_lost){
    Info info = *((Info*)obj);
    if(!info.valid){
        return;
    }
    
    switch(info.type){
        case 'P':
            player1_hurt((Player1 *)obj, hp_lost);
    }
}
