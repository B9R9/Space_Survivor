#include "mainMenu.h"


static void displaySousTitre(SDL_Texture *sousTitre, int *counter, SDL_Renderer *render)
{
	if (*counter > 500)
		copyTextureInRenderWithRect(render, sousTitre, createRect(20, 45, 60, 3));
	if (*counter > 1200)
		*counter = 0;
}

/**
 * @brief copy dans le render l ecran d acceuil
 * 
 * @param param 
 * @param render 
 * @param fps 
 */
void displayTitle(t_menuTitle *param, SDL_Renderer *render, t_timer fps, u_int32_t *menuStep)
{
	int deltaTime;

	deltaTime = fps.delta + (33 - fps.delta);
	param->timeCounter += deltaTime;
	// copyTextureInRenderWithRect(render,param->titre, createRect(5, 28, 90, 11));
	copyTextureInRenderWithRect(render,param->exit, createRect(73, 95, 25, 2));
	displaySousTitre(param->sousTitre, &param->timeCounter, render);
	if (*menuStep & transition)
		deltaTime = 1033;
	animAsteroid(param->asteroid_t, &param->asteroid_l, render, deltaTime, param->impact_t);
	if (*menuStep & transition && param->asteroid_l == NULL)
		*menuStep = mainmenu;	
}