/*
Description et purpose du fichier
*/

#ifndef _MAININTRO_H
#define _MAININTRO_H

/*includes SDL Functions*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "utilsSDL.h"

#include "fonduAnim.h"

#define FILE1 "/Users/flagada/Desktop/v2/01-Asset/img/HIveLogo.bmp"
#define FILE2 "/Users/flagada/Desktop/v2/01-Asset/img/TeamBrucie.bmp"
#define FILE3 "/Users/flagada/Desktop/v2/01-Asset/img/Geo.png"


/*Prototype*/
e_bool mainIntro(SDL_Renderer *render);

#endif