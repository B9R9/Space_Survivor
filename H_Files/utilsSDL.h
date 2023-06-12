/*
Description et purpose du fichier
*/

#ifndef _UTILSSDL_H
#define _UTILSSDL_H

/*ENUM*/
typedef enum {
	FAIL = 0,
	SUCCESS = 1,
	FALSE = 0,
	TRUE = 1
}	e_bool;

/*includes SDL Functions*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "param.h"
#include <math.h>
#include "utils.h"

void clearRender(SDL_Renderer *render);
void fullCopyTextureInRender(SDL_Texture *texture, SDL_Renderer *render);
void copyTextureInRenderWithRect(SDL_Renderer *render, SDL_Texture *texture, SDL_Rect container);
void displayRender(SDL_Renderer *render);

SDL_Texture *createTextureFromSurface(SDL_Surface *surf, SDL_Renderer *render);

SDL_Surface *imgToSurface(const char *file);
SDL_Texture *imgToTexture(const char *file, SDL_Renderer *render);

TTF_Font *set_font(int size, int fontIndex);

SDL_Texture *createTextureFromText(const char *text, int fontIndex, size_t size, const char *color, SDL_Renderer *render);
SDL_Surface *createSurfaceFromText(const char *text, int fontIndex, size_t size, u_int32_t colorValue);

SDL_Color colorConverter(u_int32_t hexValue, int alphaValue);
u_int32_t hexConverter(const char *hexvalue);
void    toColor(const char *hexValue,int alphaValue, SDL_Renderer *render);

SDL_Rect createRect(int x, int y, int w, int h);
SDL_Rect defineRect(int x, int y, int w, int h);
void copyRectInRender(SDL_Rect rect, int options, SDL_Renderer *render, char *color, int alphaValue);

void drawContour(char *color, int alphaValue, SDL_Rect rect, SDL_Renderer *render);

#endif