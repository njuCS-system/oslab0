#ifndef SCREEN_H
#define SCREEN_H

#include "component.h"

#define OBJ_MAX 20


typedef struct Screen{
    void* obj[OBJ_MAX];
    int index;
}Screen;


void screen_init();

void screen_draw();

void screen_add(void *);

void screen_clear();

void screen_rm(void *);





#endif