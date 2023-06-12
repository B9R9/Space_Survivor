/*
Description et purpose du fichier
*/

#ifndef _MAINGAME_H
#define _MAINGAME_H

/*includes SDL Functions*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "utilsSDL.h"

/*include Game*/
#include "mainMenu.h"
#include "gameRun.h"
#include "param.h"

/*Prototype*/
e_bool mainGame(SDL_Renderer *render);
#endif