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
        case 'p':
            player2_hurt((Player2 *)obj, hp_lost);
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
            return player1_isCrash((Player1 *)obj);
            break;
        case 'p':
            return player1_isCrash((Player1 *)obj);
            break;
    }

    return false;
}

int battle_virtual_get_attack(void *obj)
{
    Info info = *((Info*)obj);
    if(!info.valid){
        return -1;
    }
    
    switch(info.type){
        case 'I':
            return planeI_get_attack((PlaneI *)obj);
            break;
        case 'T':
            return planeT_get_attack((PlaneT *)obj);
            break;
        case 'U':
            return planeU_get_attack((PlaneU *)obj);
            break;
        case 'X':
            return planeX_get_attack((PlaneX *)obj);
            break;
        case 'P':
            return player1_get_attack((Player1 *)obj);
            break;
        case 'p':
            return player1_get_attack((Player1 *)obj);
            break;
        case 'B':
            return bullet_get_attack((Bullet *)obj);
            break;
    }

    return -1;
}

void battle_virtual_set_attack(void *obj, int attack)
{
    Info info = *((Info*)obj);
    if(!info.valid){
        return;
    }
    
    switch(info.type){
        case 'I':
            planeI_set_attack((PlaneI *)obj, attack);
            break;
        case 'T':
            planeT_set_attack((PlaneT *)obj, attack);
            break;
        case 'U':
            planeU_set_attack((PlaneU *)obj, attack);
            break;
        case 'X':
            planeX_set_attack((PlaneX *)obj, attack);
            break;
        case 'P':
            player1_set_attack((Player1 *)obj, attack);
            break;
        case 'p':
            player1_set_attack((Player1 *)obj, attack);
            break;
        case 'B':
            bullet_set_attack((Bullet *)obj, attack);
            break;
    }
}

int battle_virtual_get_hp(void *obj)
{
    Info info = *((Info*)obj);
    if(!info.valid){
        return -1;
    }
    
    switch(info.type){
        case 'I':
            return planeI_get_hp((PlaneI *)obj);
            break;
        case 'T':
            return planeT_get_hp((PlaneT *)obj);
            break;
        case 'U':
            return planeU_get_hp((PlaneU *)obj);
            break;
        case 'X':
            return planeX_get_hp((PlaneX *)obj);
            break;
        case 'P':
            return player1_get_hp((Player1 *)obj);
            break;
        case 'p':
            return player1_get_hp((Player1 *)obj);
            break;
    }

    return -1;
}