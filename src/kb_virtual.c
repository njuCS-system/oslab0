#include "kb_virtual.h"

void kb_virtual_answer(void* obj, int keycode){
    Info info = *((Info*)obj);
    if(!info.valid){
        return;
    }
    

}