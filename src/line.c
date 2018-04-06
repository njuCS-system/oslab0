#include "line.h"


Line_factory line_factory;


static Line* line_allocate();

static void __init__Line(Line* line,LineProperty property);

static void __finalize_Line(Line* line);

//*****************************
//构造器(们)无法多态
//****************************
Line* build_line(LineProperty property){
    //mem_alloc 
    Line* line = line_allocate();
    //constructor
    if(line!=NULL){
        __init__Line(line,property);

    }else{
        printf("[ERROR] Memory-allocate error when build a line!\n");
    }
    return line;
}



//***********************virtual functions**************************

void line_delete(Line* line){
    //destructor
    __finalize_Line(line);
    //free memory
    line->info.valid=FALSE;
}

void line_draw(Line* line){
    _FBCtlReg ctl;
    
    int color = color_to_int(line->property.color);
    int width;
    int height;
    if(is_vertical)
    {
        width = line->property.stroke;
        height = line->property.length;
    }
    else
    {
        width = line->property.length;
        height = line->property.stroke;
    }
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            color_buf[i * width + j] = color;
        }
    }
    
    ctl.x = line->property.x;
    ctl.y = line->property.y;
    ctl.w = width;
    ctl.h = height;
    ctl.pixels = color_buf;
    ctl.sync = 1;
    
    fb_add(&ctl);
}


void line_move(Line* line,int deltaX, int deltaY){
    line->property.x += deltaX;
    line->property.y += deltaY;
}



//****************************************************************

static Line* line_allocate(){
    Line* line;
    for(int i=0;i<LINE_MAX;i++){
        line=&(line_factory.__lines[line_factory.idx]);

        line_factory.idx++;
        line_factory.idx%=LINE_MAX;

        if(!line->info.valid){//遇到有效的则返回
            line->info.valid=TRUE;
            return line;
        }
    }
    return NULL;
}

static void __init__Line(Line* line,LineProperty property){
    //矩形初始化逻辑
    line->info.type = 'L';
    line->info.valid = TRUE;
    line->property = property;
}


//*****************************
//destructors
//*****************************
static void __finalize_Line(Line* line){
    //矩形的善后事宜
}
