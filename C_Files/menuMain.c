#include "mainMenu.h"


static void setMax(int *value)
{
	if (percent(SCREEN_W, *value) >= percent(SCREEN_W, 30))
		*value = percent(SCREEN_W, 10);
}

/**
 * @brief Set the Line Menu object
 * 
 * @param texture: La texture a afficher
 * @param x: coordone abcsisse
 * @param y: cooordonne ordonne
 * @param render: rendu
 */
static void setLineMenu(SDL_Texture *texture, int x, int y, SDL_Renderer *render)
{
	SDL_Rect container;

	container.x = percent(SCREEN_W, x);
	container.y = percent(SCREEN_H, y);
	container.w = percent(SCREEN_W, 15);
	container.h = percent(SCREEN_H, 3);
	setMax(&container.x);
	copyTextureInRenderWithRect(render, texture, container);
}

/**
 * @brief Set the Transition object between title et menumain
 * 
 * @param menu: specific data for menumain
 * @param param:Global data struct for menumain
 * @param render: rendu
 */
static void setTransition(t_menuMain_D menu, t_menuMain *param, SDL_Renderer *render)
{
	t_timer	fps;
	int start;
	int refY;
	int refX;

	start = -10;
	refY = 55;
	while (start < 60)
	{
		refY = 55;
		refX = start;
		startTimer(&fps.start);
		clearRender(render);
		setBackground(param->background, render);
		copyTextureInRenderWithRect(render,param->titre, createRect(5, 28, 90, 11));
		copyTextureInRenderWithRect(render,param->exit, createRect(73, 95, 25, 2));
		setLineMenu(menu.newGame_t, refX, refY, render);
		setLineMenu(menu.options_t, refX - 5, refY + 5, render);
		setLineMenu(menu.success_t, refX - 10, refY + 10, render);
		setLineMenu(menu.aboutMe_t, refX - 15, refY + 15, render);
		start = start + 1;
		displayRender(render);
		setDelta(&fps.delta, fps.start);
		setDelay(fps.delta, 33);
	}
	(*param).transition = SUCCESS;
}

/**
 * @brief Set the Menu object
 * 
 * @param redMenu data struct for display menu in red 
 * @param yellowMenu same as red menu but in Yellow
 * @param index permet la mise en evidence d ela selection en cours
 * @param render rendu
 */
static void setMenu(t_menuMain_D redMenu, t_menuMain_D yellowMenu, int index, SDL_Renderer *render)
{
	switch(index)
	{
		case (0):
			copyTextureInRenderWithRect(render, yellowMenu.newGame_t, createRect(10, 55, 15, 03));
			copyTextureInRenderWithRect(render, redMenu.options_t, createRect(10, 60, 15, 03));
			copyTextureInRenderWithRect(render, redMenu.success_t, createRect(10, 65, 15, 03));
			copyTextureInRenderWithRect(render, redMenu.aboutMe_t, createRect(10, 70, 15, 03));
			break;
		case (1):
			copyTextureInRenderWithRect(render, redMenu.newGame_t, createRect(10, 55, 15, 03));
			copyTextureInRenderWithRect(render, yellowMenu.options_t, createRect(10, 60, 15, 03));
			copyTextureInRenderWithRect(render, redMenu.success_t, createRect(10, 65, 15, 03));
			copyTextureInRenderWithRect(render, redMenu.aboutMe_t, createRect(10, 70, 15, 03));
			break;
		case (2):
			copyTextureInRenderWithRect(render, redMenu.newGame_t, createRect(10, 55, 15, 03));
			copyTextureInRenderWithRect(render, redMenu.options_t, createRect(10, 60, 15, 03));
			copyTextureInRenderWithRect(render, yellowMenu.success_t, createRect(10, 65, 15, 03));
			copyTextureInRenderWithRect(render, redMenu.aboutMe_t, createRect(10, 70, 15, 03));
			break;
		case (3):
			copyTextureInRenderWithRect(render, redMenu.newGame_t, createRect(10, 55, 15, 03));
			copyTextureInRenderWithRect(render, redMenu.options_t, createRect(10, 60, 15, 03));
			copyTextureInRenderWithRect(render, redMenu.success_t, createRect(10, 65, 15, 03));
			copyTextureInRenderWithRect(render, yellowMenu.aboutMe_t, createRect(10, 70, 15, 03));
			break;
	}
}

/**
 * @brief Display the different menu
 * 
 * @param param global struct for menu data
 * @param render rendu
 * @param fps time managment
 * @param index indique la selection en cours
 */
void displayMain(t_menuMain *param, SDL_Renderer *render, int index)
{
	int newIndex;

	newIndex = readBits(4, index);
	if (param->transition == FAIL)
		setTransition(param->menuRed, param, render);
	setMenu(param->menuRed, param->menuYellow, newIndex, render);
	copyTextureInRenderWithRect(render,param->exit, createRect(73, 95, 25, 2));
}