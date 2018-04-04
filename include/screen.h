#ifndef SCREEN_H

#define SCREEN_H
#define OBJ_MAX 1000


typedef struct Screen{
    void* obj[OBJ_MAX];
    int index;
    void (*add)(void*);
    void (*clear)();
    void (*draw)();
}Screen;




void init_screen();

#endif