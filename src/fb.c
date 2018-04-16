#include "fb.h"

static uint32_t fb_buf[_WIDTH * _HEIGHT + SAFE_OFFSET * 2];

void fb_add(_FBCtlReg *reg){
    int width = reg->w;
    int height = reg->h;
    int x = reg->x;
    int y = reg->y;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(((i + y) * _WIDTH + (j + x)) < _WIDTH * _HEIGHT && ((i + y) * _WIDTH + (j + x)) >= 0){
                Color color = int_to_color(reg->pixels[i * width + j]);
                fb_buf[SAFE_OFFSET + (i + y) * _WIDTH + (j + x)] = (color.a == 0 ? reg->pixels[i * width + j] : fb_buf[(i + y) * _WIDTH + (j + x)]);
            }
        }
    }
}

void fb_sync(){
    _FBCtlReg ctl;
    ctl.x = 0;
    ctl.y = 0;
    ctl.w = _WIDTH;
    ctl.h = _HEIGHT;
    ctl.pixels = fb_buf + SAFE_OFFSET;
    video_draw(ctl);
    draw_sync();
}

void fb_clear(){
    for(int i = 0; i < _HEIGHT * _WIDTH; i++)
    {
        fb_buf[i] = 0;
    }
}

