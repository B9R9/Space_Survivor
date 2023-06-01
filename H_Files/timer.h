/*
Description et purpose du fichier
*/

#ifndef _TIMER_H
#define _TIMER_H

/*includes SDL Functions*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "utilsSDL.h"

typedef struct	s_timer {
	int start;
	int	delta;
	int delay;
}				t_timer;

void startTimer(int *start);
void setDelta(int *delta, int start);
void setDelay(int delta, int target);
#endif