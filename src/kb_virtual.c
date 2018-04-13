#include "kb_virtual.h"

void kb_virtual_answer(void* obj, int keycode){
    Info info = *((Info*)obj);
    if(!info.valid){
        return;
    }
    
    switch(info.type)
    {
        case 'P':
            player1_answer((Player1 *)obj, keycode);
            break;
        case 'p':
            player2_answer((Player2 *)obj, keycode);
            break;
    }
}