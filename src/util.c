#include "util.h"

unsigned color_to_int(Color color)
{
    unsigned *rgb = (unsigned *)&color;
    return *rgb;
}

Color int_to_color(int rgb)
{
	Color *color = (Color *)&rgb;
	return *color;
}

RES_IDC res_idc[SIZE_OF_OBJECTSET] =
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
		{ID_BIGBOMB_0, {180 * 0, 115 + 135 * 0, 180, 180}},
		{ID_BIGBOMB_1, {180 * 1, 115 + 135 * 0, 180, 180}},
		{ID_BIGBOMB_2, {180 * 2, 115 + 135 * 0, 180, 180}},
		{ID_BIGBOMB_3, {180 * 3, 115 + 135 * 0, 180, 180}},
		{ID_BIGBOMB_4, {180 * 0, 115 + 135 * 1, 180, 180}},
		{ID_BIGBOMB_5, {180 * 1, 115 + 135 * 1, 180, 180}},
		{ID_BIGBOMB_6, {180 * 2, 115 + 135 * 1, 180, 180}},
		{ID_BIGBOMB_7, {180 * 3, 115 + 135 * 1, 180, 180}}
	};
