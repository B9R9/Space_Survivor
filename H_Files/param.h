/*
Description et purpose du fichier
*/

#ifndef _PARAM_H
#define _PARAM_H

#define SCREEN_W 800
#define SCREEN_H 600

#define BACKGROUND "/Users/flagada/Desktop/v2/01-Asset/texture/Space Background.png"
#define ROGUE1 "/Users/flagada/Desktop/v2/01-Asset/texture/rogue1.png"

enum gamePart {
	reset = 0x00,
	menu = 0x01,
	game = 0x02,
	quit = 0x04
};

#define PRSTART 0
#define PRSTATTK 1
static const char fontArray[2][100] = {
	"/Users/flagada/Desktop/v2/01-Asset/font/prstart.ttf",
	"/Users/flagada/Desktop/v2/01-Asset/font/prstartk.ttf",
};

/*Color*/
#define YELLOW "E4D00A"
#define WHITE "FFFFFF"
#define RED "9A1300"
#define BLACK "000000"
#define GREY "BCBCBC"
#define GREY2 "DDDDDD"
#define VIOLET "#8E44AD"
#define GREEN "#27AE60"

/*SpaceShipData*/
typedef struct s_spaceShipData {
	char	*color;
}				t_spaceShipData;


static const t_spaceShipData g_spaceShipArr [6] = {
	{
		.color = YELLOW
	},
	{
		.color = WHITE
	},
	{
		.color = RED
	},
	{
		.color = GREY
	},
	{
		.color = VIOLET
	},
	{
		.color = GREEN
	},
};

/*LVLData*/

typedef struct s_lvlData {
	char *backgroundPath;
}		t_lvlData;

static const t_lvlData g_LvlData [3] = {
	{
		.backgroundPath = "/Users/flagada/Desktop/v2/01-Asset/texture/Space Background.png"
	},
	{
		.backgroundPath = "/Users/flagada/Desktop/v2/01-Asset/texture/Space Background.png"
	},
	{
		.backgroundPath = "/Users/flagada/Desktop/v2/01-Asset/texture/Space Background.png"
	}
};
#endif