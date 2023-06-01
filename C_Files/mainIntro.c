#include "mainIntro.h"

static e_bool displayIntro(SDL_Renderer *render, const char *file, double time)
{
	SDL_Texture *texture;
	double		duration;

	duration = time / (double)2;
	texture = imgToTexture(file, render);
	if (texture == NULL)
		return (FAIL);
	fonduAuJour(render, texture, duration);
	fonduAuNoir(render, texture, duration);
	SDL_DestroyTexture(texture);
	return (SUCCESS);
}

e_bool mainIntro(SDL_Renderer *render)
{
	if (displayIntro(render, FILE1, 0.1) == FAIL)
		return (FAIL);
	if (displayIntro(render, FILE2, 0.1) == FAIL)
		return (FAIL);
	if (displayIntro(render, FILE3, 0.1) == FAIL)
		return (FAIL);
	return (SUCCESS);
}