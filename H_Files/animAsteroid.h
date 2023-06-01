/*
Description et purpose du fichier
*/

#ifndef _ANIMASTEROID_H
#define _ANIMASTEROID_H

/*includes SDL Functions*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "utilsSDL.h"
#include "utils.h"
#include "param.h"

typedef struct s_element {
    SDL_Rect    position;
    SDL_Texture *texture;
    // e_bool      background;
    int         speed;
    int         angle;
    float       rotate;
    float       speedRotate;
    int         indexAnim;
    int         timeAnim;  
    struct s_element *next;
}   t_element;

/*include C-Librairy*/
#include <stdio.h>

/*Include Game*/
#include "timer.h"
#include "event.h"
#include "textureToList.h"

e_bool animAsteroid(t_textureToLi *asteroid_t, t_element **asteroid_l,\
                    SDL_Renderer *render, int deltaTime, t_textureToLi *impact_t);

#endif
