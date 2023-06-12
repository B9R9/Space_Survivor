/*
Description et purpose du fichier
*/

#ifndef _GAMERUN_H
#define _GAMERUN_H

/*includes SDL Functions*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "utilsSDL.h"
#include "utils.h"
#include "param.h"
#include "timer.h"
#include "textureToList.h"

typedef	struct s_move
{
	int	up;
	int down;
	int left;
	int	right;
}				t_move;

#include "player.h"
#include "event.h"

typedef	struct s_game
{
	SDL_Texture		*background;
	t_textureToLi	*backgroundView;
	u_int32_t		gamePart;
	int				indexBackground;
	t_move			direction;

}				t_game;

/*prototype*/

e_bool gameRun(SDL_Renderer *render, u_int32_t param, u_int32_t *gameStep);

#endif
