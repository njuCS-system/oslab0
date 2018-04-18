#ifndef CP_VIRTUAL_H
#define CP_VIRTUAL_H

#include "component.h"

void cp_virtual_delete(void *);

void cp_virtual_draw(void *);

void cp_virtual_move(void*, int deltaX, int deltaY);

void cp_virtual_locate(void*, UTIL_RECT *ur);

bool cp_virtual_isPlayer(void *obj);

bool cp_virtual_isPlayer1(void *obj);

bool cp_virtual_isPlayer2(void *obj);

bool cp_virtual_isBullet(void *obj);

bool cp_virtual_isEnemyBullet(void *obj);

bool cp_virtual_isEnemy(void *obj);

void cp_virtual_toRect(void *obj, UTIL_RECT *ur);

#endif