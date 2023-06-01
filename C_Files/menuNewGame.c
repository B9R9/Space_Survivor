#include "mainMenu.h"


void displayNewGame(t_menuNewGame *param, SDL_Renderer *render, u_int32_t *menuStep, int *index)
{
	(void)param;
	(void)menuStep;
	(void)index;
	SDL_Rect selectionBox;
	SDL_Rect detailsBox;
	SDL_Rect confirmBox;
	SDL_Rect unitBox;
	SDL_Rect spaceBox;

	int selection;
	int newIndex;
	int limitX;
	int limitY;
	int i;
	int max;
	static int prevIndex;
	int startIndex;
	static int followIndex;
	static SDL_Rect scr;
	static SDL_Rect dest;

	selection = -1;
	newIndex = readBits(4, *index);
	if ((*index & 0x80) == 0)
		selection = readBits(4, (*index >> 4));
	printf("Selection %d\n", selection);
	startIndex = 5;
	SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);
	SDL_QueryTexture(param->background, NULL, NULL, &max, NULL);
	unitBox.x = percent(SCREEN_W, 50);
	unitBox.y = percent(SCREEN_H, 20);
	unitBox.w = percent(SCREEN_W, 15);
	unitBox.h = percent(SCREEN_H, 12);

	selectionBox = createRect(45, 10, 45, 70);
	detailsBox = createRect(10, 10, 25, 70);
	confirmBox = createRect(65, 85, 25, 10);

	toColor(GREY, 175, render);
	SDL_RenderFillRect(render, &detailsBox);
	SDL_RenderFillRect(render, &selectionBox);
	SDL_RenderFillRect(render, &confirmBox);
	toColor(RED, 255, render);
	SDL_RenderDrawRect(render, &selectionBox);
	SDL_RenderDrawRect(render, &detailsBox);
	if (newIndex == 6 || selection > -1)
			toColor(YELLOW, 255, render);
	SDL_RenderDrawRect(render, &confirmBox);

	
	limitX = percent(SCREEN_W, 45) + percent(SCREEN_W, 45);
	limitY = percent(SCREEN_H, 10) + percent(SCREEN_H, 70);
	i = 0;
	scr.y = 0;
	scr.w = 5; 
	scr.h = 100;
	if (prevIndex == newIndex)
	{
		startIndex = followIndex;
		scr.x = followIndex;
		if (scr.x >= max)
		{	scr.x = 0;
			followIndex = 0;}
	}
	else
		scr.x = startIndex;
	while (1)
	{
		if (i != newIndex)
			SDL_RenderCopy(render, param->background, NULL, &unitBox);
		if (i == newIndex || selection == i)
		{
			dest.x = unitBox.x;
			dest.y = unitBox.y;
			dest.w = 2;
			dest.h = unitBox.h;
			toColor(YELLOW, 255, render);
			while (dest.x < unitBox.w + unitBox.x)
			{
				SDL_RenderCopy(render, param->background, &scr, &dest);
				scr.x += 2;
				dest.x += 2;
				if (scr.x >= max)
					scr.x = 0;
			}
			followIndex += 2;
		}
		else
			toColor(RED, 255, render);	
		SDL_RenderDrawRect(render, &unitBox);
		toColor(RED, 255, render);
		spaceBox.x = unitBox.x + percent(SCREEN_W, 5);
		spaceBox.y = unitBox.y + percent(SCREEN_H, 4);
		spaceBox.w = percent(SCREEN_W, 5);
		spaceBox.h = percent(SCREEN_H, 4);
		SDL_RenderFillRect(render, &spaceBox);
		unitBox.x += unitBox.w + percent(SCREEN_W, 5);
		if (unitBox.x + unitBox.w + percent(SCREEN_W, 1) >= limitX)
		{
			unitBox.x = percent(SCREEN_W, 50);
			unitBox.y += unitBox.h + percent(SCREEN_H, 5);
			if (unitBox.y + unitBox.h + percent(SCREEN_H, 5) >= limitY)
				break ; 
		}
		i++;
	}
	prevIndex = newIndex;
}