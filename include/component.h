#ifndef COMPONENT_H
#define COMPONENT_H
#include "util.h"
#include "amdev.h"

char __type[]={
    'R',//rectangle
    'L' //line
};

typedef struct Info{
    volatile char type;//record the type of an object
    volatile boolean valid;

}Info;

typedef struct RectProperty{
    int x,y,width,height; //位置和大小
    char r,g,b;//颜色
    int stroke;//线宽
}RectProperty;

typedef struct Rect{
    volatile Info info;
    volatile _FBCtlReg reg;
}Rect;


void __init__Rect(Rect* ,RectProperty);

void draw(void*);





#endif