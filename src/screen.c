#include "screen.h"
#include "component.h"

Screen screen;



static void __add(Screen* s,void* object);

static void __draw(Screen* s);

static void __clear(Screen* s);

void screen_add(void *obj){
    __add(&screen,obj);
}


void screen_clear(){
    __clear(&screen);
}



void screen_draw(){
    __draw(&screen);
}

void screen_rm(void * obj){

}


//****************************************************************
static void __add(Screen* s,void* object){
    if(s->index >= OBJ_MAX){
        // printf("[ERROR] Screen buffer overflow!");
    }
    s->obj[s->index++]=object;

}

static void __draw(Screen* s){
    for(int i=0;i < s->index;i++){
        cp_virtual_draw(s->obj[i]);
    }
}
static void __clear(Screen* s){
    for(int i=0;i < s->index;i++){
        cp_virtual_delete(s->obj[i]);
    }
    s->index=0;
}
