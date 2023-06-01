#include "graphic.h"

/*
**	Clean la structure t_screen 
**	et permet la fermeture SDL
*/
void	destroyScreen(t_screen *screen)
{
	if (screen->render)
		SDL_DestroyRenderer(screen->render);
	if (screen->window)
		SDL_DestroyWindow(screen->window);
	SDL_Quit();
}

/*
**	Creation d une nouvelle fenetre
*/
static e_bool newWindow(SDL_Window **window, const char *title)
{
	*window = SDL_CreateWindow(title,\
    	SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,\
    	SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
	if (*window == NULL)
		return (errPrint("newWindow", SDL_GetError()), FAIL);
	return (SUCCESS);
}

/**
 * @brief Permet la creation d un nouveau render
 */
static e_bool newRender(SDL_Renderer **render, SDL_Window *window)
{
	*render = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if (*render == NULL)
		return (errPrint("newRender", SDL_GetError()), FAIL);
	return (SUCCESS);
}

/*
**	initialise PNG IMAGE
**
*/
static e_bool init_PNG(void)
{
	u_int32_t	imaflags;

	imaflags = IMG_INIT_PNG;
	if (!(IMG_Init(imaflags) & imaflags))
		return (errPrint("initPNG", SDL_GetError()), FAIL);
	return(SUCCESS);
}

/**
 * @brief Initialise TTF SDL
 */
static e_bool init_TTF(void)
{
	if (TTF_Init() != 0)
		return (errPrint("init_TTF", SDL_GetError()), FAIL);
	return (SUCCESS);
}

/*
**	initialise SDL en mode Video
**	le parametre de SDL_Init est un bitflag est peut etre modifie selon les besoins
*/
static e_bool init_SDL(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return (errPrint("init_SDL", SDL_GetError()), FAIL);
	return (SUCCESS);
}

/*
**	Permet la creation d un nouvelle ecran(render & window)
*/
e_bool newScreen(t_screen *screen)
{
	if (init_SDL() == FAIL)
		return (destroyScreen(screen), FAIL);
	if (newWindow(&screen->window, "Space Survivor") == FAIL)
		return (destroyScreen(screen), FAIL);
	if (newRender(&screen->render, screen->window) == FAIL)
		return (destroyScreen(screen), FAIL);
	if (init_PNG() == FAIL)
		return (destroyScreen(screen), FAIL);
	if (init_TTF() == FAIL)
		return (destroyScreen(screen), FAIL);
	return (SUCCESS);
}