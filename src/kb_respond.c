#include "kb_respond.h"

KbRespond kbRespond;

static void __add(KbRespond* s,void* object);

static void __action(KbRespond* s);

static void __clear(KbRespond* s);

static void __remove(KbRespond* s,void* object);


void kbRespond_init()
{
    memset(kbRespond.obj, 0 ,sizeof(void *) * OBJ_MAX);
    kbRespond.index = 0;
    __clear(&kbRespond);
}


void kbRespond_add(void *obj){
    __add(&kbRespond,obj);
}


void kbRespond_clear(){
    __clear(&kbRespond);
}



void kbRespond_draw(){
    __action(&kbRespond);
}

void kbRespond_rm(void * obj){
    __remove(&kbRespond, obj);
}


//****************************************************************
static void __add(KbRespond* s,void* object){
    int now_index = s->index - 1;
    if(now_index < 0)
    {
        now_index += OBJ_MAX;
    }
    for(; s->obj[i] != NULL && s->index != now_index; s->index = (s->index + 1)%OBJ_MAX);    
    if(s->index == now_index)
    {
        printf("[ERROR] KbRespond buffer overflow!\n");
    }
    else
    {
        s->obj[s->index] = object;
    }
    
}

static void __action(KbRespond* s){
    _KbdReg reg = read_key();
    if(reg.keydown == 0)
    {
        return;
    }
    for(int i = 0;i < OBJ_MAX;i++){
        if(s->obj[i] != NULL)
            kb_virtual_answer(s->obj[i], reg.keycode);
    }
}
static void __clear(KbRespond* s){
    for(int i=0;i < OBJ_MAX;i++){
        s->obj[i] = NULL;
    }
    s->index=0;
}


static void __remove(KbRespond* s, void *obj)
{
    int index = 0;
    for(; obj != s->obj[index] && index < OBJ_MAX; index++);
    
    if(index >= 0 && index < OBJ_MAX && s->obj[i] != NULL)
    {
        s->obj[i] = NULL;
    }
    else 
    {
        printf("[ERROR] The Object is invalid!\n");
    }
}