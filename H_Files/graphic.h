

/*
Description et purpose du fichier
*/

#ifndef _GRAPHIC_H
#define _GRAPHIC_H

/*includes SDL Functions*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "utilsSDL.h"

#include "param.h"
#include "utils.h"

/*STRUCT*/
typedef struct	s_screen {
	SDL_Renderer	*render;
	SDL_Window		*window;
}				t_screen;

/*Prototype*/
void	destroyScreen(t_screen *screen);
e_bool	newScreen(t_screen *screen);
#endif