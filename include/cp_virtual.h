#ifndef CP_VIRTUAL_H
#define CP_VIRTUAL_H

#include "component.h"

void cp_virtual_delete(void *);

void cp_virtual_draw(void *);

void cp_virtual_move(void*, int deltaX, int deltaY);

void cp_virtual_locate(void*, UTIL_RECT *ur);


#endif