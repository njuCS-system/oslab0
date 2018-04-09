#include "big_explosion3.h"


BigExplosion3_factory bigExplosion3_factory;


static BigExplosion3* bigExplosion3_allocate();

static void __init__BigExplosion3(BigExplosion3* bigExplosion3,BigExplosion3Property property);

static void __finalize_BigExplosion3(BigExplosion3* bigExplosion3);

//*****************************
//构造器(们)无法多态
//****************************
BigExplosion3* build_bigExplosion3(BigExplosion3Property property){
    //mem_alloc 
    BigExplosion3* bigExplosion3 = bigExplosion3_allocate();
    //constructor
    if(bigExplosion3!=NULL){
        __init__BigExplosion3(bigExplosion3,property);

    }else{
        printf("[ERROR] Memory-allocate error when build a bigExplosion3!\n");
    }
    return bigExplosion3;
}



//***********************virtual functions**************************

void bigExplosion3_delete(BigExplosion3* bigExplosion3){
    //destructor
    __finalize_BigExplosion3(bigExplosion3);
    //free memory
    bigExplosion3->info.valid=FALSE;
}

void bigExplosion3_draw(BigExplosion3* bigExplosion3){
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

    for(int i = 0; i <= height; i++)
    {
        for(int j = 0; j <= width; j++)
        {
            Color temp_color;
            temp_color.b = bmpHead -> pixels[((i + y) * pic_width + (j + x)) * 3];
            temp_color.g = bmpHead -> pixels[((i + y) * pic_width + (j + x)) * 3 + 1];
            temp_color.r = bmpHead -> pixels[((i + y) * pic_width + (j + x)) * 3 + 2];
            if(temp_color.b == 255 && temp_color.g == 0 && temp_color.r == 255)
            {
                temp_color.a = temp_color.r = temp_color.g = temp_color.b = 1;
                //temp_color.a = 1;
            }
            else
            {
                temp_color.a = 0;
            }
            color_buf[i * width + j] = color_to_int(temp_color);
        }
    }
    
    ctl.x = bigExplosion3->property.x;
    ctl.y = bigExplosion3->property.y;
    ctl.pixels = color_buf;
    ctl.w = width;
    ctl.h = height;
    ctl.sync = 0;

    _Device *dev = getdev(&video_dev, _DEV_VIDEO);
    dev->write(_DEVREG_VIDEO_FBCTL, &ctl, sizeof(_FBCtlReg));
    draw_sync();

    fb_add(&ctl);
}


void bigExplosion3_move(BigExplosion3* bigExplosion3,int deltaX, int deltaY){
    bigExplosion3->property.x += deltaX;
    bigExplosion3->property.y += deltaY;
}

void bigExplosion3_automove(BigExplosion3* bigExplosion3){
    bigExplosion3->property.x += bigExplosion3->property.vx;
    bigExplosion3->property.y += bigExplosion3->property.vy;
}



//****************************************************************

static BigExplosion3* bigExplosion3_allocate(){
    BigExplosion3* bigExplosion3;
    for(int i=0;i<BIGEXPLOSION_MAX;i++){
        bigExplosion3=&(bigExplosion3_factory.__bigExplosion3s[bigExplosion3_factory.idx]);

        bigExplosion3_factory.idx++;
        bigExplosion3_factory.idx%=BIGEXPLOSION_MAX;

        if(!bigExplosion3->info.valid){//遇到有效的则返回
            bigExplosion3->info.valid=TRUE;
            return bigExplosion3;
        }
    }
    return NULL;
}

static void __init__BigExplosion3(BigExplosion3* bigExplosion3,BigExplosion3Property property){
    //初始化逻辑
    bigExplosion3->info.type = '3';
    bigExplosion3->info.valid = TRUE;
    bigExplosion3->property = property;
}


//*****************************
//destructors
//*****************************
static void __finalize_BigExplosion3(BigExplosion3* bigExplosion3){
    //善后事宜
}
