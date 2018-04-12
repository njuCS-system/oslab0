#include "game.h"

Game game;
static int init_x = 0;

//                         x  y vx vy size h_max attack
static PlaneIProperty i = {0, 0, 0, 1, 1, 100, 20};
static PlaneXProperty x = {0, 0, 0, 1, 1, 200, 30};
static PlaneTProperty t = {0, 0, 0, 2, 1, 200, 80};
static PlaneUProperty u = {0, 0, 0, 3, 1, 400, 50};

//                                        x                              y                 size hp_max attack
static Player1Property p1 =  {_WIDTH / 2 - PLANE_WIDTH / 2, _HEIGHT - HP_OFFSET - PLANE_HEIGHT, 1, 1000, 80};

static void __add(Game* s,void* object);

static void __draw(Game* s);

static void __clear(Game* s);

static void __remove(Game* s,void* object);

static void __move(Game* s);

static void __bullet(Game *s);

static void __boundary(Game *s);

static void __bullet_hurt(Game *s);

static void game_init();

static void game_add(void *obj);

static void game_clear();

static void game_draw();

static void game_rm(void * obj);

static void game_move();

static void random_create_plane();

static void create_bullet();

static void boundary_detect();

static bool is_inside_collision(UTIL_RECT *ur1, UTIL_RECT *ur2);

static bool is_outside_collision(UTIL_RECT *ur1, UTIL_RECT *ur2);

static void bullet_hurt();

static void random_init_x()
{
    init_x = rand() % (_WIDTH - PLANE_WIDTH);
}

void main_loop()
{
    game_clear();
    game_init();

    const int delay = 100;
    const int shooting_loop_count = 10;

    unsigned now_time = uptime();
    unsigned last_time = 0;
    srand(now_time);
    int loop_count = 0;
    while(1)
    {
        if(now_time >= last_time + delay)
        {
            random_create_plane();
            if(loop_count % shooting_loop_count == 0)
            {
                create_bullet();
            }
            game_move();
            boundary_detect();
            bullet_hurt();
            kbRespond_action();
            game_draw();
            last_time = now_time;
            loop_count++;
        }
        now_time = uptime();
    }
    
}

bool is_point_inside(Rect_Points rp, Point p)
{
    if(p.x >= rp.p1.x && p.x >= rp.p3.x && p.x <= rp.p2.x && p.x <= rp.p4.x
     &&p.y >= rp.p1.y && p.y >= rp.p2.y && p.y <= rp.p3.y && p.y <= rp.p4.y)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

bool is_inside_collision(UTIL_RECT *ur1, UTIL_RECT *ur2)
{
    Rect_Points rp1 = {{ur1->x, ur1->y}, {ur1->x + ur1->w, ur1->y}, {ur1->x, ur1->y + ur1->h}, {ur1->x + ur1->w, ur1->y + ur1->h}};
    Rect_Points rp2 = {{ur2->x, ur2->y}, {ur2->x + ur2->w, ur2->y}, {ur2->x, ur2->y + ur2->h}, {ur2->x + ur2->w, ur2->y + ur2->h}};
    //if(ur2->x != 0){
    //    printf("rp1 = (%d %d) (%d %d) (%d %d) (%d %d) rp2 = (%d %d) (%d %d) (%d %d) (%d %d)\n"
    //, rp1.p1.x, rp1.p1.y, rp1.p2.x, rp1.p2.y ,rp1.p3.x ,rp1.p3.y, rp1.p4.x, rp1.p4.y, rp2.p1.x, rp2.p1.y, rp2.p2.x, rp2.p2.y ,rp2.p3.x ,rp2.p3.y, rp2.p4.x, rp2.p4.y);
    //}
    if((is_point_inside(rp1, rp2.p1) && is_point_inside(rp1, rp2.p2) && is_point_inside(rp1, rp2.p3) && is_point_inside(rp1, rp2.p4))
     ||(is_point_inside(rp2, rp1.p1) && is_point_inside(rp2, rp1.p2) && is_point_inside(rp2, rp1.p3) && is_point_inside(rp2, rp1.p4)))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    
}

bool is_outside_collision(UTIL_RECT *ur1, UTIL_RECT *ur2)
{
    Rect_Points rp1 = {{ur1->x, ur1->y}, {ur1->x + ur1->w, ur1->y}, {ur1->x, ur1->y + ur1->h}, {ur1->x + ur1->w, ur1->y + ur1->h}}; 
    Rect_Points rp2 = {{ur2->x, ur2->y}, {ur2->x + ur2->w, ur2->y}, {ur2->x, ur2->y + ur2->h}, {ur2->x + ur2->w, ur2->y + ur2->h}};
    /*printf("rp1 = (%d %d) (%d %d) (%d %d) (%d %d) rp2 = (%d %d) (%d %d) (%d %d) (%d %d)\n"
    , rp1.p1.x, rp1.p1.y, rp1.p2.x, rp1.p2.y ,rp1.p3.x ,rp1.p3.y, rp1.p4.x, rp1.p4.y, rp2.p1.x, rp2.p1.y, rp2.p2.x, rp2.p2.y ,rp2.p3.x ,rp2.p3.y, rp2.p4.x, rp2.p4.y);
    */
    if((is_point_inside(rp1, rp2.p1) || is_point_inside(rp1, rp2.p2) || is_point_inside(rp1, rp2.p3) || is_point_inside(rp1, rp2.p4))
     ||(is_point_inside(rp2, rp1.p1) || is_point_inside(rp2, rp1.p2) || is_point_inside(rp2, rp1.p3) || is_point_inside(rp2, rp1.p4)))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static void create_bullet()
{
    __bullet(&game);
}

static void boundary_detect()
{
    __boundary(&game);
}

static void random_create_plane()
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

static void bullet_hurt()
{
    __bullet_hurt(&game);
}

static void game_init()
{
    memset(game.obj, 0 ,sizeof(void *) * OBJ_MAX);
    game.index = 0;
    screen_init();

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

static void __bullet(Game *s)
{
    const int bullet_speed = 10;
    const int bullet_offset = 10;
    for(int i = 0;i < OBJ_MAX;i++){
        if(((Info *)(s->obj[i]))->valid == TRUE){
            UTIL_RECT ur;
            cp_virtual_locate(s->obj[i], &ur);
            if(cp_virtual_isPlayer(s->obj[i]))
            {
                //                     x            y           vx       vy      size            attack
                BulletProperty b0 = {ur.x, ur.y - bullet_offset, 0, -bullet_speed, 2, battle_virtual_get_attack(s->obj[i])};
                BulletProperty b1 = {ur.x + PLANE_WIDTH / 2, ur.y - bullet_offset, 0, -bullet_speed, 2, battle_virtual_get_attack(s->obj[i])};
                BulletProperty b2 = {ur.x + PLANE_WIDTH, ur.y - bullet_offset, 0, -bullet_speed, 2, battle_virtual_get_attack(s->obj[i])};

                Bullet *bullet0 = build_bullet(b0);
                Bullet *bullet1 = build_bullet(b1);
                Bullet *bullet2 = build_bullet(b2);

                game_add(bullet0);
                game_add(bullet1);
                game_add(bullet2);
            }
            else if(cp_virtual_isEnemy(s->obj[i]))
            {
                //TODO:
            }
        }
    }
}

static void __boundary(Game *s)
{
    for(int i = 0;i < OBJ_MAX;i++){
        if(((Info *)(s->obj[i]))->valid == TRUE){
            UTIL_RECT ur_obj;
            cp_virtual_locate(s->obj[i], &ur_obj);
            //                   x  y     w        h
            UTIL_RECT ur_game = {0, 0, _WIDTH, _HEIGHT};
            if(cp_virtual_isBullet(s->obj[i]) || cp_virtual_isEnemy(s->obj[i]))
            {
                if(is_outside_collision(&ur_obj, &ur_game) == TRUE && is_inside_collision(&ur_obj, &ur_game) == FALSE)
                {
                    game_rm(s->obj[i]);
                }
            }
            else if(cp_virtual_isPlayer(s->obj[i]))
            {
                //TODO:
            }
        }
    }
}

static void __bullet_hurt(Game *s)
{
    for(int i = 0;i < OBJ_MAX;i++){
        if(((Info *)(s->obj[i]))->valid == TRUE && cp_virtual_isBullet(s->obj[i]) == TRUE)
        {
            UTIL_RECT ur_bullet;
            cp_virtual_locate(s->obj[i], &ur_bullet);
            if(cp_virtual_isEnemyBullet(s->obj[i]))
            {
                for(int j = 0; j < OBJ_MAX; j++)
                {
                    if(((Info *)(s->obj[j]))->valid == TRUE && cp_virtual_isPlayer(s->obj[j]) == TRUE)
                    {
                        //TODO:
                    }
                }
            }
            else
            {
                for(int j = 0; j < OBJ_MAX; j++)
                {
                    if(((Info *)(s->obj[j]))->valid == TRUE && cp_virtual_isEnemy(s->obj[j]) == TRUE)
                    {
                        UTIL_RECT ur_enemy;
                        cp_virtual_locate(s->obj[j], &ur_enemy);
                        if(is_inside_collision(&ur_bullet, &ur_enemy))
                        {
                            battle_virtual_hurt(s->obj[j], battle_virtual_get_attack(s->obj[i]));
                            game_rm(s->obj[i]);
                            if(battle_virtual_isCrash(s->obj[j]))
                            {
                                game_rm(s->obj[j]);
                            }
                            break;
                        }
                    }
                }
            }
        }
    }
}