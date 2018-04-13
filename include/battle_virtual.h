#ifndef BATTLE_VIRTUAL_H
#define BATTLE_VIRTUAL_H

#include "component.h"

void battle_virtual_hurt(void *, int);

bool battle_virtual_isCrash(void *obj);

int battle_virtual_get_attack(void *);

void battle_virtual_set_attack(void *, int);

int battle_virtual_get_hp(void *);

#endif
