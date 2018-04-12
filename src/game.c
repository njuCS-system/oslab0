#include "game.h"

Game game;
static int init_x = 0;

//                         x  y vx  vy size h_max
static PlaneIProperty i = {0, 0, 0, 1, 1, 100};
static PlaneXProperty x = {0, 0, 0, 1, 1, 200};
static PlaneTProperty t = {0, 0, 0, 2, 1, 200};
static PlaneUProperty u = {0, 0, 0, 3, 1, 400};

//                                 x            x     size hp_max
static Player1Property p1 =  {_WIDTH / 2, HEIGHT - 10, 1, 1000}

static void __add(Game* s,void* object);

static void __draw(Game* s);

static void __clear(Game* s);

static void __remove(Game* s,void* object);

static void __move(Game* s);

static void game_init();

static void game_add(void *obj);

static void game_clear();

static void game_draw();

static void game_rm(void * obj);

static void game_move();

void random_create_plane();


void random_init_x()
{
    init_x = rand() % (_WIDTH - PLANE_WIDTH);
}

void main_loop()
{
    game_clear();
    game_rm(NULL);
    game_init();

    const int delay = 30;

    unsigned now_time = uptime();
    unsigned last_time = 0;
    srand(now_time);
    while(1)
    {
        if(now_time >= last_time + delay)
        {
            random_create_plane();
            game_move();
            kbRespond_action();
            game_draw();
            last_time = now_time;
        }
        now_time = uptime();
    }
    
}

static void game_init()
{
    memset(game.obj, 0 ,sizeof(void *) * OBJ_MAX);
    game.index = 0;
    screen_init();

    p1.x = init_x;
    Player1 *player1 = build_player1(p1);
    kbRespond_add(player1);
    game_add(player1);
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

static void game_move()
{
    __move(&game);
}

void random_create_plane()
{
    const int random_range = 1000;
    const int plane_occur = random_range * 0.1;
    const int planeI_occur = plane_occur * 0.4;
    const int planeX_occur = plane_occur * 0.3 + planeI_occur;
    const int planeT_occur = plane_occur * 0.2 + planeX_occur;
    const int planeU_occur = plane_occur * 0.1 + planeT_occur;
    random_init_x();
    int r = rand() % random_range;
    if(r < plane_occur)
    {
        if(r < planeI_occur)
        {
            i.x = init_x;
            PlaneI *planeI = build_planeI(i);
            game_add(planeI);
        }
        else if(r < planeX_occur)
        {
            x.x = init_x;
            PlaneX *planeX = build_planeX(x);
            game_add(planeX);
        }
        else if(r < planeT_occur)
        {
            t.x = init_x;
            PlaneT *planeT = build_planeT(t);
            game_add(planeT);
        }
        else if(r < planeU_occur)
        {
            u.x = init_x;
            PlaneU *planeU = build_planeU(u);
            game_add(planeU);
        }
    }
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


static void __move(Game* s)
{
    for(int i = 0;i < OBJ_MAX;i++){
        if(((Info *)(s->obj[i]))->valid == TRUE){
            mv_virtual_automove(s->obj[i]);
        }
    }
}