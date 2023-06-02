#include "mainMenu.h"

void displayContainer(SDL_Renderer *render, int newIndex, int selection)
{
	SDL_Rect	shipsContainer;
	SDL_Rect	detailsContainer;
	SDL_Rect	confirmContainer;

	shipsContainer = createRect(45, 10, 45, 70);
	detailsContainer = createRect(10, 10, 25, 70);
	confirmContainer = createRect(65, 85, 25, 10);

	copyRectInRender(shipsContainer,1 ,render, GREY, 195);
	drawContour(RED, 255, shipsContainer, render);
	copyRectInRender(detailsContainer,1 ,render, GREY, 195);
	drawContour(RED, 255, detailsContainer, render);
	copyRectInRender(confirmContainer,1 ,render, GREY, 195);
	if (newIndex == 6 || selection > -1)
		drawContour(YELLOW, 255, confirmContainer, render);
	else
		drawContour(RED, 255, confirmContainer, render);
}

static void displayShips(SDL_Rect units,int index, SDL_Renderer *render)
{
	SDL_Rect	temp;
	temp.x = units.x + percent(SCREEN_W, 5);
	temp.y = units.y + percent(SCREEN_H, 4);
	temp.w = percent(SCREEN_W, 5);
	temp.h = percent(SCREEN_H, 4);
	toColor(g_spaceShipArr[index].color, 255, render); 
	SDL_RenderFillRect(render, &temp);
}

static SDL_Rect	nextUnits(SDL_Rect units, int *loop)
{
	int limitY;
	int limitX;

	limitY = percent(SCREEN_H, 10) + percent(SCREEN_H, 70);
	limitX = percent(SCREEN_W, 45) + percent(SCREEN_W, 45);

	units.x += units.w + percent(SCREEN_W, 5);
	if (units.x + units.w + percent(SCREEN_W, 1) >= limitX)
	{
		units.x = percent(SCREEN_W, 50);
		units.y += units.h + percent(SCREEN_H, 5);
		if (units.y + units.h + percent(SCREEN_H, 5) >= limitY)
			*loop = FALSE; 
	}
	return (units);
}

static SDL_Rect defineRect(int x, int y, int w, int h)
{
	SDL_Rect	temp;

	temp.x = x;
	temp.y = y;
	temp.w = w;
	temp.h = h;
	return (temp);
}

static void backgroundAnimation(int newIndex, int max, SDL_Rect units, SDL_Renderer *render, SDL_Texture *texture)
{
	int 		startIndex;
	static int	previousIndex;
	static int	currentIndex;
	SDL_Rect	src;
	SDL_Rect	dst;

	startIndex = 5;
	src = defineRect(startIndex, 0, 5, 100);
	dst = defineRect(units.x, units.y, 2, units.h);
	if (previousIndex == newIndex)
	{
		startIndex = currentIndex;
		src.x = currentIndex;
		if (src.x >= max)
		{	
			src.x = 0;
			currentIndex = 0;
		}
	}
	while (dst.x < units.w + units.x)
	{
		SDL_RenderCopy(render, texture, &src, &dst);
		src.x += 2;
		dst.x += 2;
		if (src.x >= max)
			src.x = 0;
	}
	currentIndex += 2;
	previousIndex = newIndex;
}

static void displayUnits(SDL_Renderer *render, int newIndex, int selection, SDL_Texture *background)
{
	SDL_Rect	units;
	int			i;
	int			loop;
	int			max;

	i = 0;
	loop = TRUE;
	units = createRect(50, 20, 15, 12);
	SDL_QueryTexture(background, NULL, NULL, &max, NULL);
	while(loop)
	{
		toColor(RED, 255, render);
		if (i != newIndex)
			SDL_RenderCopy(render, background, NULL, &units);
		if (i == newIndex || i == selection)
		{
			backgroundAnimation(newIndex, max, units, render, background);
			toColor(YELLOW,255, render);
		}
		SDL_RenderDrawRect(render, &units);
		displayShips(units, i, render);
		units = nextUnits(units, &loop);
		i++;
	}
}

static void setIndexAndSelection(int *newIndex, int *selection, int index)
{
	*newIndex = readBits(4, index);
	*selection = -1;
	if ((index & 0x80) == 0)
		*selection = readBits(4, (index >> 4));
}

void displayNewGame(t_menuNewGame *param, SDL_Renderer *render, u_int32_t *menuStep, int *index)
{
	(void)menuStep;
	int selection;
	int newIndex;
	
	SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
	setIndexAndSelection(&newIndex, &selection, *index);
	displayContainer(render, newIndex, selection);
	displayUnits(render,newIndex, selection, param->background);
}