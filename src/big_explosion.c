#include "big_explosion.h"


BigExplosion_factory bigExplosion_factory;


static BigExplosion* bigExplosion_allocate();

static void __init__BigExplosion(BigExplosion* bigExplosion,BigExplosionProperty property);

static void __finalize_BigExplosion(BigExplosion* bigExplosion);

//*****************************
//构造器(们)无法多态
//****************************
BigExplosion* build_bigExplosion(BigExplosionProperty property){
    //mem_alloc 
    BigExplosion* bigExplosion = bigExplosion_allocate();
    //constructor
    if(bigExplosion!=NULL){
        __init__BigExplosion(bigExplosion,property);

    }else{
        printf("[ERROR] Memory-allocate error when build a bigExplosion!\n");
    }
    return bigExplosion;
}



//***********************virtual functions**************************

void bigExplosion_delete(BigExplosion* bigExplosion){
    //destructor
    __finalize_BigExplosion(bigExplosion);
    //free memory
    bigExplosion->info.valid=FALSE;
}

void bigExplosion_draw(BigExplosion* bigExplosion){
    _FBCtlReg ctl;

    BITMAPINFOHEADER *bmpHead = (BITMAPINFOHEADER*) (model_objset + BITMAPFILEHEADER_LENGTH);
    RECT temp_rect = res_idc[ID_BIGBOMB_3].rect;
    long pic_width = bmpHead -> biWidth;
    //long pic_height = bmpHead -> biHeight;
    unsigned width = temp_rect.w;
    unsigned height = temp_rect.h;
    int x = temp_rect.x;
    int y = temp_rect.y;
    printf("%d %d %d %d %d\n", pic_width, width, height, y, x);

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            Color temp_color;
            temp_color.b = bmpHead -> pixels[((i + y) * pic_width + (j + x)) * 3];
            temp_color.g = bmpHead -> pixels[((i + y) * pic_width + (j + x)) * 3 + 1];
            temp_color.r = bmpHead -> pixels[((i + y) * pic_width + (j + x)) * 3 + 2];
            if(temp_color.b == 255 && temp_color.g == 0 && temp_color.r == 255)
            {
                //temp_color.a = temp_color.r = temp_color.g = temp_color.b = 1;
                temp_color.a = 1;
            }
            else
            {
                temp_color.a = 0;
            }
            color_buf[i * width + j] = color_to_int(temp_color);
        }
    }
    
    ctl.x = bigExplosion->property.x;
    ctl.y = bigExplosion->property.y;
    ctl.pixels = color_buf;
    ctl.w = width;
    ctl.h = height;
    ctl.sync = 0;

    _Device *dev = getdev(&video_dev, _DEV_VIDEO);
    dev->write(_DEVREG_VIDEO_FBCTL, &ctl, sizeof(_FBCtlReg));
    draw_sync();

    fb_add(&ctl);
}


void bigExplosion_move(BigExplosion* bigExplosion,int deltaX, int deltaY){
    bigExplosion->property.x += deltaX;
    bigExplosion->property.y += deltaY;
}

void bigExplosion_automove(BigExplosion* bigExplosion){
    bigExplosion->property.x += bigExplosion->property.vx;
    bigExplosion->property.y += bigExplosion->property.vy;
}



//****************************************************************

static BigExplosion* bigExplosion_allocate(){
    BigExplosion* bigExplosion;
    for(int i=0;i<BIGEXPLOSION_MAX;i++){
        bigExplosion=&(bigExplosion_factory.__bigExplosions[bigExplosion_factory.idx]);

        bigExplosion_factory.idx++;
        bigExplosion_factory.idx%=BIGEXPLOSION_MAX;

        if(!bigExplosion->info.valid){//遇到有效的则返回
            bigExplosion->info.valid=TRUE;
            return bigExplosion;
        }
    }
    return NULL;
}

static void __init__BigExplosion(BigExplosion* bigExplosion,BigExplosionProperty property){
    //初始化逻辑
    bigExplosion->info.type = 'E';
    bigExplosion->info.valid = TRUE;
    bigExplosion->property = property;
}


//*****************************
//destructors
//*****************************
static void __finalize_BigExplosion(BigExplosion* bigExplosion){
    //善后事宜
}
