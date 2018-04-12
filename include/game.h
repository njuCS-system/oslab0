#ifndef GAME_H
#define GAME_H

#include "util.h"
#include "io_util.h"
#include "component.h"
#include "screen.h"
#include "kb_respond.h"

//in srceen.h
//#define OBJ_MAX 100
#define HP_OFFSET 20

typedef struct Game{
    void* obj[OBJ_MAX];
    int index;
}Game;

//p1                 p2
//********************
//*                  *
//*                  *
//*                  *
//********************
//p3                 p4
typedef struct Rect_Points
{
    Point p1;
    Point p2;
    Point p3;
    Point p4;
}Rect_Points;

void main_loop();

#endif