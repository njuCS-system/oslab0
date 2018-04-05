#include "util.h"

int color_to_int(Color color)
{
    int *return_val = (int *)&color;
    return *return_val;
}
