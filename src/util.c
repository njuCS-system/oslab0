#include "util.h"

unsigned color_to_int(Color color)
{
    unsigned *return_val = (int *)&color;
    return *return_val;
}
