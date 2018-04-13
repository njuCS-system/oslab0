#include "player2.h"


Player2_factory player2_factory;


static Player2* player2_allocate();

static void __init__Player2(Player2* player2,Player2Property property);

static void __finalize_Player2(Player2* player2);

//*****************************
//构造器(们)无法多态
//****************************
Player2* build_player2(Player2Property property){
    //mem_alloc 
    Player2* player2 = player2_allocate();
    //constructor
    if(player2!=NULL){
        __init__Player2(player2,property);

    }else{
        printf("[ERROR] Memory-allocate error when build a player2!\n");
    }
    return player2;
}



//***********************virtual functions**************************

void player2_delete(Player2* player2){
    //destructor
    __finalize_Player2(player2);
    //free memory
    player2->info.valid=FALSE;
}

void player2_draw(Player2* player2){
    hp_draw(player2->hp);
    int x = player2->property.x;
    int y = player2->property.y;

    _FBCtlReg ctl;

    BITMAPINFOHEADER *bmpHead = (BITMAPINFOHEADER*) (model_player2 + BITMAPFILEHEADER_LENGTH);
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
    
    ctl.x = x;
    ctl.y = y;
    ctl.pixels = color_buf;
    ctl.w = width;
    ctl.h = height;
    ctl.sync = 0;
    
    // video_draw(ctl);
    // draw_sync();
    
    fb_add(&ctl);
}


void player2_locate(Player2 *player2, UTIL_RECT *ur)
{
    ur->x = player2->property.x;
    ur->y = player2->property.y;
    BITMAPINFOHEADER *bmpHead = (BITMAPINFOHEADER*) (model_player2 + BITMAPFILEHEADER_LENGTH);
    ur->w = bmpHead -> biWidth;
    ur->h = bmpHead -> biHeight;
}


void player2_move(Player2* player2,int deltaX, int deltaY){
    player2->property.x += deltaX;
    player2->property.y += deltaY;
    hp_move(player2->hp, deltaX, deltaY);
}

void player2_answer(Player2 *player2, int keycode)
{
    printf("player2\n");
    switch(keycode)
    {
        case 49: //J
            player2_move(player2, -PLAYER2_SPEED, 0);
            break;
        case 50: //K
            player2_move(player2, 0, PLAYER2_SPEED);
            break;
        case 51: //L
            player2_move(player2, PLAYER2_SPEED, 0);
            break;
        case 36: //I
            player2_move(player2, 0, -PLAYER2_SPEED);
            break;
    }
}

void player2_hurt(Player2 *player2, int hp_lost)
{
    hp_decrease(player2->hp, hp_lost);
}

bool player2_isCrash(Player2 *player2)
{
    return player2->hp->hp_left <= 0;
}

int player2_get_attack(Player2 *player2)
{
    return player2->property.attack;
}

void player2_set_attack(Player2 *player2, int attack)
{
    player2->property.attack = attack;
}

int player2_get_hp(Player2 *player2)
{
    return player2->hp->hp_left;
}

//****************************************************************

static Player2* player2_allocate(){
    Player2* player2;
    for(int i=0;i<PLAYER2_MAX;i++){
        player2=&(player2_factory.__player2s[player2_factory.idx]);

        player2_factory.idx++;
        player2_factory.idx%=PLAYER2_MAX;

        if(!player2->info.valid){//遇到有效的则返回
            player2->info.valid=TRUE;
            return player2;
        }
    }
    return NULL;
}

static void __init__Player2(Player2* player2,Player2Property property){
    //初始化逻辑
    player2->info.type = 'p';
    player2->info.valid = TRUE;
    player2->property = property;
    
    int x = player2->property.x;
    int y = player2->property.y;
    //              x  y size        hp_max          is_player
    HpProperty h = {x, y, 2, player2->property.hp_max, TRUE};
    player2->hp = build_hp(h);
}


//*****************************
//destructors
//*****************************
static void __finalize_Player2(Player2* player2){
    //善后事宜
    hp_delete(player2->hp);
}
