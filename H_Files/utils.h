/*
Description et purpose du fichier
*/

#ifndef _UTILS_H
#define _UTILS_H

/*includes SDL Functions*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "utilsSDL.h"

/*include C-Librairy*/
#include <stdio.h>

/*Include Game*/
#include "param.h"


/*Prototype*/
void errPrint(const char *location, const char *error);

e_bool run(u_int32_t gameSteps);

int percent(int total, int value);

int	randomnbr(int min, int max);

void setBackground(SDL_Texture *background, SDL_Renderer *render);

int readBits(int nbBits, int value);
#endif
