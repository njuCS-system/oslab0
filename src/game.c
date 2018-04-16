#include "game.h"

Game game;
static int init_x = 0;

//                         x  y vx vy size h_max attack
static PlaneIProperty i = {0, 0, 0, 1, 1, 60, 20};
static PlaneXProperty x = {0, 0, 0, 1, 1, 300, 30};
static PlaneTProperty t = {0, 0, 0, 2, 1, 120, 80};
static PlaneUProperty u = {0, 0, 0, 3, 1, 200, 50};

//                                        x                              y                 size hp_max attack
static Player1Property p1 =  {_WIDTH / 3 - PLANE_WIDTH / 2, _HEIGHT - HP_OFFSET - PLANE_HEIGHT, 1, 1000, 80};
static Player1Property p2 =  {2 * _WIDTH / 3 - PLANE_WIDTH / 2, _HEIGHT - HP_OFFSET - PLANE_HEIGHT, 1, 1000, 80};

static void __add(Game* s,void* object);

static void __draw(Game* s);

static void __clear(Game* s);

static void __remove(Game* s,void* object);

static void __move(Game* s);

static void __create_player_bullet(Game *s);

static void __create_enemy_bullet(Game *s);

static void __boundary(Game *s);

static void __collision_detect(Game *s);

static void game_init();

static void game_add(void *obj);

static void game_clear();

static void game_draw();

static void game_rm(void * obj);

static void game_move();

static void random_create_plane();

static void create_player_bullet();

static void create_enemy_bullet();

static void boundary_detect();

static bool is_inside_collision(UTIL_RECT *ur1, UTIL_RECT *ur2);

static bool is_outside_collision(UTIL_RECT *ur1, UTIL_RECT *ur2);

static void collision_detect();

static void random_init_x()
{
    init_x = rand() % (_WIDTH - PLANE_WIDTH);
}

void main_loop()
{
    game_clear();
    game_init();

    const int delay = 0;
    const int shooting_loop_count = 40;


    unsigned now_time = uptime();
    unsigned last_time = 0;
    srand(now_time);
    int loop_count = 0;
    while(1)
    {
        if(now_time >= last_time + delay)
        {
            // int test_time = uptime();
            // int new_time = 0;
            random_create_plane();
            
            // new_time = uptime();
            // printf("create plane: %d\n", new_time - test_time);
            // test_time = new_time;
            
            if(loop_count % shooting_loop_count == 0)
            {
                create_player_bullet();
                create_enemy_bullet();
            }

            // new_time = uptime();
            // printf("create bullet: %d\n", new_time - test_time);
            // test_time = new_time;

            game_move();

            // new_time = uptime();
            // printf("game move: %d\n", new_time - test_time);
            // test_time = new_time;

            boundary_detect();

            // new_time = uptime();
            // printf("boundary: %d\n", new_time - test_time);
            // test_time = new_time;

            collision_detect();

            // new_time = uptime();
            // printf("collision: %d\n", new_time - test_time);
            // test_time = new_time;

            kbRespond_action();

            // new_time = uptime();
            // printf("kb: %d\n", new_time - test_time);
            // test_time = new_time;

            game_draw();

            // new_time = uptime();
            // printf("draw: %d\n", new_time - test_time);
            // test_time = new_time;

            last_time = now_time;
            loop_count++;

            //while(1);
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

static void create_player_bullet()
{
    __create_player_bullet(&game);
}

static void create_enemy_bullet()
{
    __create_enemy_bullet(&game);
}

static void boundary_detect()
{
    __boundary(&game);
}

static void random_create_plane()
{
    const int random_range = 10000;
    const int plane_occur = random_range * 0.005;
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

static void collision_detect()
{
    __collision_detect(&game);
}

static void game_init()
{
    memset(game.obj, 0 ,sizeof(void *) * OBJ_MAX);
    game.index = 0;
    screen_init();

    Player1 *player1 = build_player1(p1);
    kbRespond_add(player1);
    game_add(player1);

    Player2 *player2 = build_player2(p2);
    kbRespond_add(player2);
    game_add(player2);
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

static void __create_player_bullet(Game *s)
{
    const int bullet_speed = 8;
    const int bullet_offset = 10;
    //我们假设player只能出现在前两个单元！
    for(int i = 0;i < 2;i++){
        if(((Info *)(s->obj[i]))->valid == TRUE){
            UTIL_RECT ur;
            cp_virtual_locate(s->obj[i], &ur);
            if(cp_virtual_isPlayer(s->obj[i]))
            {
                //                     x            y           vx       vy      size            attack
                
                BulletProperty b0 = {ur.x + PLANE_WIDTH / 2, ur.y - bullet_offset, 0, -bullet_speed, BULLET_SIZE, battle_virtual_get_attack(s->obj[i])};
                Bullet *bullet0 = build_bullet(b0);
                game_add(bullet0);

                /*BulletProperty b0 = {ur.x + PLANE_WIDTH / 3, ur.y - bullet_offset, 0, -bullet_speed, 2, battle_virtual_get_attack(s->obj[i])};
                BulletProperty b1 = {ur.x + 2 * PLANE_WIDTH / 3, ur.y - bullet_offset, 0, -bullet_speed, 2, battle_virtual_get_attack(s->obj[i])};
                
                Bullet *bullet0 = build_bullet(b0);
                Bullet *bullet1 = build_bullet(b1);
                
                game_add(bullet0);
                game_add(bullet1);
                */
            }
        }
    }
}

static void __create_enemy_bullet(Game *s)
{
    const int bullet_speed = 8;
    const int bullet_offset = 10;
    const int random_range = 1000;
    const int attack = random_range * 1;
    for(int i = 0;i < OBJ_MAX;i++){
        if(((Info *)(s->obj[i]))->valid == TRUE){
            UTIL_RECT ur;
            cp_virtual_locate(s->obj[i], &ur);
            if(cp_virtual_isEnemy(s->obj[i]) && (rand()%random_range) < attack)
            {
                //                     x            y           vx       vy      size            attack
                BulletProperty b0 = {ur.x + PLANE_WIDTH / 3, ur.y + bullet_offset + PLANE_HEIGHT, 0, bullet_speed, BULLET_SIZE, battle_virtual_get_attack(s->obj[i])};
                Bullet *bullet0 = build_bullet(b0);

                game_add(bullet0);
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
            if(cp_virtual_isEnemy(s->obj[i]))
            {
                if(is_outside_collision(&ur_obj, &ur_game) == TRUE && is_inside_collision(&ur_obj, &ur_game) == FALSE)
                {
                    game_rm(s->obj[i]);
                }
            }
            else if(cp_virtual_isBullet(s->obj[i]))
            {
                if(is_outside_collision(&ur_obj, &ur_game) == FALSE && is_inside_collision(&ur_obj, &ur_game) == FALSE)
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

static void __collision_detect(Game *s)
{
    for(int i = 0;i < OBJ_MAX;i++){
        if(((Info *)(s->obj[i]))->valid == TRUE && cp_virtual_isBullet(s->obj[i]) == TRUE)
        {
            UTIL_RECT ur_bullet;
            cp_virtual_locate(s->obj[i], &ur_bullet);
            if(cp_virtual_isEnemyBullet(s->obj[i]))
            {
                //我们假设player只能出现在前两个单元！
                for(int j = 0; j < 2; j++)
                {
                    if(((Info *)(s->obj[j]))->valid == TRUE && cp_virtual_isPlayer(s->obj[j]) == TRUE)
                    {
                        UTIL_RECT ur_player;
                        cp_virtual_locate(s->obj[j], &ur_player);
                        if(is_inside_collision(&ur_bullet, &ur_player))
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

    //我们假设player只能出现在前两个单元！
    for(int i = 0; i < 2; i++){
        if(((Info *)(s->obj[i]))->valid == TRUE && cp_virtual_isPlayer(s->obj[i]) == TRUE)
        {
            UTIL_RECT ur_player;
            cp_virtual_locate(s->obj[i], &ur_player);
            for(int j = i + 1; j < OBJ_MAX; j++)
            {
                if(((Info *)(s->obj[j]))->valid == TRUE && cp_virtual_isEnemy(s->obj[j]) == TRUE)
                {
                    UTIL_RECT ur_enemy;
                    cp_virtual_locate(s->obj[j], &ur_enemy);
                    if(is_outside_collision(&ur_player, &ur_enemy))
                    {
                        battle_virtual_hurt(s->obj[i], battle_virtual_get_hp(s->obj[j]));
                        game_rm(s->obj[j]);
                        if(battle_virtual_isCrash(s->obj[i]))
                        {
                            game_rm(s->obj[i]);
                        }
                        break;
                    }
                }
            }
        }
    }
}