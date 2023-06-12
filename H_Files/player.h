/*
Description et purpose du fichier
*/

#ifndef _PLAYER_H
#define _PLAYER_H

/*includes SDL Functions*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "utilsSDL.h"
#include "utils.h"
#include "param.h"
#include "gameRun.h"


typedef struct s_coord {
	int x;
	int y;
	int w;
	int h;
}			t_coord;

typedef struct s_player 
{
	char 		*color;
	int 		live;
	t_coord		position;
}		t_player;

/*prototype*/
void newPlayer(t_player *newPlayer, int shipIndex);
void playerPosition(SDL_Renderer *render, t_player *player, t_move direction);

#endif