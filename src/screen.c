#include "screen.h"
#include "component.h"

Screen screen;

static void __add(Screen* s,void* object);

static void __draw(Screen* s);

static void __clear(Screen* s);

static void __remove(Screen* s,void* object);


void screen_init()
{
    memset(screen.obj, 0 ,sizeof(void *) * OBJ_MAX);
    screen.index = 0;
}


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
    __remove(&screen, obj);
}


//****************************************************************
static void __add(Screen* s,void* object){
    /*if(s->index >= OBJ_MAX){
        //printf("[ERROR] Screen buffer overflow!");
    }
    s->obj[s->index++]=object;*/

    int now_index = s->index - 1;
    if(now_index < 0)
    {
        now_index += OBJ_MAX;
    }
    for(; ((Info *)(s->obj[s->index]))->valid == FALSE && s->index != now_index; s->index = (s->index + 1)%OBJ_MAX);    
    if(s->index == now_index)
    {
        printf("[ERROR] Screen buffer overflow!\n");
    }
    else
    {
        s->obj[s->index] = object;
    }
    
}

static void __draw(Screen* s){
    fb_clear();
    for(int i = 0;i < OBJ_MAX;i++){
        if(((Info *)(s->obj[i]))->valid == TRUE)
            cp_virtual_draw(s->obj[i]);
    }
    fb_sync();
}
static void __clear(Screen* s){
    for(int i=0;i < OBJ_MAX;i++){
        if(((Info *)(s->obj[i]))->valid == TRUE)
            cp_virtual_delete(s->obj[i]);
    }
    s->index=0;
}


static void __remove(Screen* s, void *obj)
{
    int index = 0;
    for(; obj == s->obj[index] && index < OBJ_MAX; index++);
    
    if(index >= 0 && index < OBJ_MAX && ((Info *)(s->obj[index]))->valid == TRUE)
    {
        cp_virtual_delete(s->obj[index]);
    }
    else 
    {
        printf("[ERROR] The Object is invalid!\n");
    }
}