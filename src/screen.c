#include "screen.h"

Screen screen;

static void __add(Screen* s,void* object);

static void __draw(Screen* s);

static void __clear(Screen* s);

static void __remove(Screen* s,void* object);


void screen_init()
{
    memset(screen.obj, 0 ,sizeof(void *) * OBJ_MAX);
    screen.index = 0;
    fb_clear();
    fb_sync();
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
    for(; ((Info *)(s->obj[s->index]))->valid == TRUE && s->index != now_index; s->index = (s->index + 1)%OBJ_MAX);    
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
    int test_time = uptime();
    int new_time = 0;
    fb_clear();

    new_time = uptime();
    printf("clear: %d\n", new_time - test_time);
    test_time = new_time;

    for(int i = 0;i < OBJ_MAX;i++){
        if(((Info *)(s->obj[i]))->valid == TRUE){
            cp_virtual_draw(s->obj[i]);
            //printf("%d, %c\n", i, ((Info*)&s->obj[i])->type);
        }
    }

    new_time = uptime();
    printf("add: %d\n", new_time - test_time);
    test_time = new_time;

    fb_sync();

    new_time = uptime();
    printf("sync: %d\n", new_time - test_time);
    test_time = new_time;
}
static void __clear(Screen* s){
    for(int i=0;i < OBJ_MAX;i++){
        if(((Info *)(s->obj[i]))->valid == TRUE){
            cp_virtual_delete(s->obj[i]);
        }
    }
    s->index=0;
}


static void __remove(Screen* s, void *obj)
{
    if(obj == NULL)
    {
        return;
    }
    
    int index = 0;
    for(; obj != s->obj[index] && index < OBJ_MAX; index++);
    
    if(index >= 0 && index < OBJ_MAX && ((Info *)(s->obj[index]))->valid == TRUE)
    {
        cp_virtual_delete(s->obj[index]);
    }
    else 
    {
        printf("[ERROR] The Screen Object is invalid!\n");
    }
}