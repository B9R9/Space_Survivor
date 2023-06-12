/*
Description et purpose du fichier
*/

#ifndef _EVENT_H
#define _EVENT_H

/*includes SDL Functions*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "utilsSDL.h"
#include "param.h"
#include "gameRun.h"

#include "mainMenu.h"

/*Prototype*/
void checkEventMenu(u_int32_t *gameStep, u_int32_t *index);
void checkEventIntro(e_bool *pass);
void checkEventGame(u_int32_t *step, t_move *direction);
#endif