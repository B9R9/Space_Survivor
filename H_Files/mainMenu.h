/*
Description et purpose du fichier
*/

#ifndef _MAINMENU_H
#define _MAINMENU_H

/*includes SDL Functions*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "utilsSDL.h"

#include "animAsteroid.h"
#include "textureToList.h"
#include "param.h"
#include "timer.h"
#include "event.h"

enum menuPart {
	init = 0x00,
	title = 0x01,
	mainmenu = 0x02,
	newGame = 0x04,
	lvl		= 0x08,
	option = 0x10,
	success = 0x20,
	aboutMe = 0x40,
	quitM = 0x80,
	transition = 0x100
};

/*STRUCT*/

typedef struct s_rectCoord {
	int x;
	int y;
	int w;
	int h;
}			t_rectCoord;

typedef struct	s_menuTitle {
	SDL_Texture 			*background;
	SDL_Texture 			*titre;
	SDL_Texture 			*sousTitre;
	SDL_Texture 			*exit;
	struct s_textureToLi	*asteroid_t;
	struct s_element		*asteroid_l;
	struct s_textureToLi	*impact_t;
	int						timeCounter;
}				t_menuTitle;

typedef struct s_menuMain_D {
    SDL_Texture *newGame_t;
    SDL_Texture *options_t;
    SDL_Texture *aboutMe_t;
    SDL_Texture *success_t;
}				t_menuMain_D;

typedef struct s_menuMain {
	struct s_menuMain_D	menuRed;
	struct s_menuMain_D	menuYellow;
	e_bool				transition;
	SDL_Texture 			*background;
	SDL_Texture 			*titre;
	SDL_Texture 			*exit;
	int						index;
}				t_menuMain;

typedef struct s_menuNewGame {
	SDL_Texture 			*background;
	SDL_Texture 			*selectionShipText;
	SDL_Texture 			*notAvailable;
	// SDL_Texture				*rogue1; // Texture non valable
	SDL_Rect				rogue1;
	int						selection;

}				t_menuNewGame;

typedef struct	s_menuParam {
	struct s_menuTitle		title;
	struct s_menuMain		main;
	struct s_menuNewGame	new;
	int					index;

}				t_menuParam;

/*Prototype*/
e_bool	mainMenu(SDL_Renderer *render, u_int32_t *gameStep);
void	displayTitle(t_menuTitle *param, SDL_Renderer *render, t_timer fps, u_int32_t *menuStep);
void	displayMain(t_menuMain *param, SDL_Renderer *render, int index);
void	displayNewGame(t_menuNewGame *param, SDL_Renderer *render, u_int32_t *menuStep, int *index);
void	displayLvlSelection(SDL_Renderer *render, int index);
void	displayContainer(SDL_Renderer *render, int newIndex, int selection, int indexConfirm);
void	setIndexAndSelection(int *newIndex, int *selection, int index, int option);
#endif