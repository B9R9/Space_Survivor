/*
Description et purpose du fichier
*/

#ifndef _TEXTURETOLIST_H
#define _TEXTURETOLIST_H

/*includes SDL Functions*/
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "utilsSDL.h"

typedef struct	s_textureToLi {
	int						id;
	size_t					sizeLi;
	SDL_Texture				*texture;
	struct s_textureToLi	*next;
}				t_textureToLi;

#define ASTEROID 0
#define IMPACT 1

typedef struct	s_textureParam {
	const char	*path;
	size_t		columnsSize;
	size_t		lineSize;
	size_t		totalElement;
	size_t		x;
	size_t		y;
}				t_textureParam;

static const t_textureParam g_textureParam[2] = {
	{
		.path = "/Users/flagada/Desktop/v2/01-Asset/texture/sprite_Sheet_Asteroide.png",
		.columnsSize = 8,
		.lineSize = 8,
		.totalElement = 64,
		.x = 0,
		.y = 0
	},
	{
		.path = "/Users/flagada/Desktop/v2/01-Asset/texture/impact.png",
		.columnsSize = 5,
		.lineSize = 2,
		.totalElement = 7,
		.x = 0,
		.y = 0

	}
};


t_textureToLi *newTextureLi(int indexTexture, SDL_Renderer *render);
#endif