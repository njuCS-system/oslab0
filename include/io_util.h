#ifndef IO_UTIL_H
#define IO_UTIL_H

#include "util.h"

uint32_t uptime();
_KbdReg read_key();
void video_draw(_FBCtlReg clt);
void draw_sync();

#endif