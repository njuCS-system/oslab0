#include "util.h"

unsigned color_to_int(Color color)
{
    unsigned *return_val = (unsigned *)&color;
    return *return_val;
}


/*_Device *getdev(_Device **ptr, uint32_t id) {
  if (*ptr) return *ptr;
  for (int n = 1; ; n ++) {
    _Device *cur = _device(n);
    if (cur->id == id) {
      *ptr = cur;
      return cur;
    }
    if (!cur) break;
  }
  //assert(0);
  return NULL;
}


void draw_sync() {
  _Device *dev = getdev(&video_dev, _DEV_VIDEO);
  _FBCtlReg ctl;
  ctl.pixels = NULL;
  ctl.x = ctl.y = ctl.w = ctl.h = 0;
  ctl.sync = 1;
  dev->write(_DEVREG_VIDEO_FBCTL, &ctl, sizeof(ctl));
}*/
