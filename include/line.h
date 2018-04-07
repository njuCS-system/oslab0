#ifndef LINE_H
#define LINE_H

#include "util.h"


#define LINE_MAX 100


typedef struct LineProperty{
    int x,y,length;//位置和大小
    Color color;//颜色
    int stroke;//线宽
    bool is_vertical;
}LineProperty;


typedef struct Line{
    volatile Info info;
    volatile LineProperty property;
}Line;

typedef struct Line_factory{
    Line __lines[LINE_MAX];
    int idx;
}Line_factory;


Line* build_line();

//*******************virtual functions***********************

//绘制
void line_draw(Line* );

//移动
void line_move(Line*,int,int);

//删除
void line_delete(Line* );




#endif
