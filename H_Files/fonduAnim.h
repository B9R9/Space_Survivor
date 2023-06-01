/*
Description et purpose du fichier
*/

#ifndef _FONDUANIM_H
#define _FONDUANIM_H

/*includes SDL Functions*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "utilsSDL.h"

/*include C-Librairy*/
#include <stdio.h>

/*Include Game*/
#include "timer.h"
#include "event.h"

void fonduAuJour(SDL_Renderer *render, SDL_Texture *texture, double stime);
void fonduAuNoir(SDL_Renderer *render, SDL_Texture *texture, double stime);


#endif