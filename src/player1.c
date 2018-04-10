#include "player1.h"


Player1_factory player1_factory;


static Player1* player1_allocate();

static void __init__Player1(Player1* player1,Player1Property property);

static void __finalize_Player1(Player1* player1);

//*****************************
//构造器(们)无法多态
//****************************
Player1* build_player1(Player1Property property){
    //mem_alloc 
    Player1* player1 = player1_allocate();
    //constructor
    if(player1!=NULL){
        __init__Player1(player1,property);

    }else{
        printf("[ERROR] Memory-allocate error when build a player1!\n");
    }
    return player1;
}



//***********************virtual functions**************************

void player1_delete(Player1* player1){
    //destructor
    __finalize_Player1(player1);
    //free memory
    player1->info.valid=FALSE;
}

void player1_draw(Player1* player1){
    _FBCtlReg ctl;

    BITMAPINFOHEADER *bmpHead = (BITMAPINFOHEADER*) (model_player1 + BITMAPFILEHEADER_LENGTH);
    long width = bmpHead -> biWidth;
    long height = bmpHead -> biHeight;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            Color temp_color;
            temp_color.b = bmpHead -> pixels[(i * width + j) * 3];
            temp_color.g = bmpHead -> pixels[(i * width + j) * 3 + 1];
            temp_color.r = bmpHead -> pixels[(i * width + j) * 3 + 2];
            if(temp_color.b == 1 && temp_color.g == 1 && temp_color.r == 1)
            {
                temp_color.a = 1;
            }
            else
            {
                temp_color.a = 0;
            }
            color_buf[i * width + j] = color_to_int(temp_color);
        }
    }
    
    ctl.x = player1->property.x;
    ctl.y = player1->property.y;
    ctl.pixels = color_buf;
    ctl.w = width;
    ctl.h = height;
    ctl.sync = 0;

    _Device *dev = getdev(&video_dev, _DEV_VIDEO);
    dev->write(_DEVREG_VIDEO_FBCTL, &ctl, sizeof(_FBCtlReg));
    draw_sync();

    fb_add(&ctl);
}


void player1_move(Player1* player1,int deltaX, int deltaY){
    player1->property.x += deltaX;
    player1->property.y += deltaY;
}

//****************************************************************

static Player1* player1_allocate(){
    Player1* player1;
    for(int i=0;i<PLAYER1_MAX;i++){
        player1=&(player1_factory.__player1s[player1_factory.idx]);

        player1_factory.idx++;
        player1_factory.idx%=PLAYER1_MAX;

        if(!player1->info.valid){//遇到有效的则返回
            player1->info.valid=TRUE;
            return player1;
        }
    }
    return NULL;
}

static void __init__Player1(Player1* player1,Player1Property property){
    //初始化逻辑
    player1->info.type = 'P';
    player1->info.valid = TRUE;
    player1->property = property;
}


//*****************************
//destructors
//*****************************
static void __finalize_Player1(Player1* player1){
    //善后事宜
}
