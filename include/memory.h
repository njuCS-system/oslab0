#ifndef MEMORY_H

#define MEMORY_H

#define RECT_MAX 100

#include "component.h"

typedef struct Rect_factory{
    Rect __rects[RECT_MAX];
    int idx;
    Rect* (*build)(RectProperty property);
    void (*free)(Rect*);
}Rect_factory;


void free(void*);

void init_memory()




#endif