#include "util.h"

unsigned color_to_int(Color color)
{
    unsigned *return_val = (unsigned *)&color;
    return *return_val;
}
