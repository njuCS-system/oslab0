#ifndef KB_RESPOND_H
#define KB_RESPOND_H

#include "component.h"
#include "util.h"

#define KB_MAX 20


typedef struct KbRespond{
    void* obj[KB_MAX];
    int index;
}KbRespond;

void kbRespond_init();

void kbRespond_action();

void kbRespond_add(void *);

void kbRespond_clear();

void kbRespond_rm(void *);

void kbRespond_disable(char ch);



#endif