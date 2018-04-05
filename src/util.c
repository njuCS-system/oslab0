#include "util.h"

int color_to_int(Color color)
{
    int *return_val = (int *)&color;
    return *return_val;
}

static _Device *getdev(_Device **ptr, uint32_t id) {
  if (*ptr) return *ptr;
  for (int n = 1; ; n ++) {
    _Device *cur = _device(n);
    if (cur->id == id) {
      *ptr = cur;
      return cur;
    }
    if (!cur) break;
  }
  assert(0);
  return NULL;
}
