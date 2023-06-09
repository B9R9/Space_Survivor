#include "mainMenu.h"

static SDL_Rect nextLvlUnits(SDL_Rect units, int *loop)
{
	int limitY;
	int limitX;

	limitY = percent(SCREEN_H, 10) + percent(SCREEN_H, 70);
	limitX = percent(SCREEN_W, 45) + percent(SCREEN_W, 45);
	units.x += units.w + percent(SCREEN_W, 5);
	if (units.x + units.w + percent(SCREEN_W, 10) >= limitX)
	{
		units.x = percent(SCREEN_W, 50);
		units.y += units.h + percent(SCREEN_H, 5);
		if (units.y + units.h + percent(SCREEN_H, 5) >= limitY)
			*loop = FALSE; 
	}
	return (units);
}

static void displayLvlUnits(SDL_Renderer *render, int newIndex, int lvlSelection)
{
	SDL_Rect	lvlUnits;
	int			i;
	int			loop;
	// int			max;

	i = 0;
	loop = TRUE;
	lvlUnits = createRect(50, 20, 15, 14);
	// max = 1024;
	// SDL_QueryTexture(background, NULL, NULL, &max, NULL);
	while (loop)
	{
		copyRectInRender(lvlUnits, 1, render, GREEN, 255);
		copyRectInRender(lvlUnits, 0, render, GREY, 255);
		if (i == newIndex || i == lvlSelection)
			copyRectInRender(lvlUnits, 0, render, YELLOW, 255);
		lvlUnits = nextLvlUnits(lvlUnits, &loop);
		i++;
	}
}

void	displayLvlSelection(SDL_Renderer *render, int index)
{
	int lvlSelection;
	int newIndex;

	SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
	setIndexAndSelection(&newIndex, &lvlSelection, index, 1);
	printf("*******************************************\n");
	printf("LVL SECTION: Your ship is %d \n", readBits(4, (index >> 4)));
	printf("LVL SECTION: Your selection is %d \n", lvlSelection);
	printf("LVL SECTION: Your newindex(1) is %d \n", readBits(4, index));
	printf("LVL SECTION: Your newIndex is %d \n", newIndex);
	printf("LVL SECTION: Your Index is %d \n", index);
	displayContainer(render, newIndex, lvlSelection, 3);
	displayLvlUnits(render, newIndex, lvlSelection);
}