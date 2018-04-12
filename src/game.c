#include "game.h"

Game game;
static int init_x = 0;
static int init_y = 0;
//                            x       y   vx  vy size h_max
static PlaneIProperty i = {init_x, init_y, 0, 10, 1, 100};

static void __add(Game* s,void* object);

static void __draw(Game* s);

static void __clear(Game* s);

static void __remove(Game* s,void* object);

static void game_init();

static void game_add(void *obj);

static void game_clear();

static void game_draw();

static void game_rm(void * obj);



void random_create_plane()
{

}

void main_loop()
{
    srand(uptime());
}

static void game_init()
{
    memset(game.obj, 0 ,sizeof(void *) * OBJ_MAX);
    game.index = 0;
    screen_init();
}


static void game_add(void *obj){
    __add(&game,obj);
}


static void game_clear(){
    __clear(&game);
}


static void game_draw(){
    __draw(&game);
}


static void game_rm(void * obj){
    __remove(&game, obj);
}


//****************************************************************
static void __add(Game* s,void* object){
    screen_add(object);

    int now_index = s->index - 1;
    if(now_index < 0)
    {
        now_index += OBJ_MAX;
    }
    for(; ((Info *)(s->obj[s->index]))->valid == TRUE && s->index != now_index; s->index = (s->index + 1)%OBJ_MAX);    
    if(s->index == now_index)
    {
        printf("[ERROR] Game buffer overflow!\n");
    }
    else
    {
        s->obj[s->index] = object;
    }
    
}

static void __draw(Game* s){
    screen_draw();
}


static void __clear(Game* s){
    screen_clear();
    s->index=0;
}


static void __remove(Game* s, void *obj)
{
    screen_rm(obj);
}