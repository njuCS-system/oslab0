#include "kb_util.h"

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
  //assert(0);
  return NULL;
}

static _Device *input_dev;

_KbdReg read_key() {
  _Device *dev = getdev(&input_dev, _DEV_INPUT);
  _KbdReg key;
  dev->read(_DEVREG_INPUT_KBD, &key, sizeof(_KbdReg));
  return key;
}