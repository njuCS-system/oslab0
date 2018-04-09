#include "util.h"

unsigned color_to_int(Color color)
{
    unsigned *return_val = (unsigned *)&color;
    return *return_val;
}

RES_IDC res_idc[] =
	{
		{ID_PLAYER, {0, 0, 29, 33}},
		{ID_ENEMY_SMALL, {41, 0, 33, 28}},
		{ID_ENEMY_MEDIUM, {74, 0, 43, 42}},
		{ID_ENEMY_BIG, {0, 33, 62, 50}},
		{ID_ROUNDBULLET_0, {29, 13, 7, 7}},
		{ID_ROUNDBULLET_1, {36, 0, 5, 5}},
		{ID_DOWNMISSILE, {29, 0, 3, 13}},
		{ID_UPMISSILE, {32, 0, 4, 8}},
		{ID_SMALLBOMB_0, {32 * 0, 83, 32, 32}},
		{ID_SMALLBOMB_1, {32 * 1, 83, 32, 32}},
		{ID_SMALLBOMB_2, {32 * 2, 83, 32, 32}},
		{ID_SMALLBOMB_3, {32 * 3, 83, 32, 32}},
		{ID_SMALLBOMB_4, {32 * 4, 83, 32, 32}},
		{ID_SMALLBOMB_5, {32 * 5, 83, 32, 32}},
		{ID_SMALLBOMB_6, {32 * 6, 83, 32, 32}},
		{ID_SMALLBOMB_7, {32 * 7, 83, 32, 32}},
		{ID_BIGBOMB_0, {180 * 0, 115 + 135 * 0, 180, 135}},
		{ID_BIGBOMB_1, {180 * 1, 115 + 135 * 0, 180, 135}},
		{ID_BIGBOMB_2, {180 * 2, 115 + 135 * 0, 180, 135}},
		{ID_BIGBOMB_3, {180 * 3, 115 + 135 * 0, 180, 135}},
		{ID_BIGBOMB_4, {180 * 0, 115 + 135 * 1, 180, 135}},
		{ID_BIGBOMB_5, {180 * 1, 115 + 135 * 1, 180, 135}},
		{ID_BIGBOMB_6, {180 * 2, 115 + 135 * 1, 180, 135}},
		{ID_BIGBOMB_7, {180 * 3, 115 + 135 * 1, 180, 135}}
	};

_Device *getdev(_Device **ptr, uint32_t id) {
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
}
