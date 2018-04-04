#include "screen.h"
#include "memory.h"

Screen screen;




static void __add(Screen* s,void* object){
    if(s->index >= OBJ_MAX){
        // printf("[ERROR] Screen buffer overflow!");
    }
    s->obj[s->index++]=object;

}

void add(void *obj){
    __add(&screen,obj);
}

static void __clear(Screen* s){
    for(int i=0;i < s->index;i++){
        free(s->obj[i]);
    }
    s->index=0;
}

void clear(){
    __clear(&screen);
}

static void __draw(Screen* s){
    for(int i=0;i < s->index;i++){
        draw(s->obj[i]);
    }
}


void draw(){
    draw(&screen);
}

void init_screen(){
    screen.add=&add;
    screen.clear=&clear;
    screen.draw=&draw;
}