#include "kb_respond.h"

KbRespond kbRespond;

static void __add(KbRespond* s,void* object);

static void __action(KbRespond* s);

static void __clear(KbRespond* s);

static void __remove(KbRespond* s,void* object);


void kbRespond_init()
{
    memset(kbRespond.obj, 0 ,sizeof(void *) * KB_MAX);
    kbRespond.index = 0;
    __clear(&kbRespond);
}


void kbRespond_add(void *obj){
    __add(&kbRespond,obj);
}


void kbRespond_clear(){
    __clear(&kbRespond);
}



void kbRespond_action(){
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
        now_index += KB_MAX;
    }
    for(; s->obj[s->index] != NULL && s->index != now_index; s->index = (s->index + 1)%KB_MAX);    
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
    for(int i = 0;i < KB_MAX;i++){
        if(s->obj[i] != NULL)
            kb_virtual_answer(s->obj[i], reg.keycode);
    }
}

static void __clear(KbRespond* s){
    for(int i=0;i < KB_MAX;i++){
        s->obj[i] = NULL;
    }
    s->index=0;
}


static void __remove(KbRespond* s, void *obj)
{
    int index = 0;
    for(; obj != s->obj[index] && index < KB_MAX; index++);
    
    if(index >= 0 && index < KB_MAX && s->obj[index] != NULL)
    {
        s->obj[index] = NULL;
    }
    else 
    {
        printf("[ERROR] The Object is invalid!\n");
    }
}