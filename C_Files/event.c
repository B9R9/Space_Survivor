#include "event.h"

static void eventMenuTitle(u_int32_t *menuStep, SDL_Event event)
{
	if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		*menuStep = quitM;
	if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
		*menuStep = transition;
}

static int setMenuMainIndex(int index, int scanCode)
{
	if (scanCode == SDL_SCANCODE_DOWN)
	{
		index = index + 1;
		if (index == 4)
			index = 0;
		return (index);
	}
	if (scanCode == SDL_SCANCODE_UP)
	{
		index = index - 1;
		if (index == -1)
			index = 3;
		return (index);
	}
	return(0);
}

static int setMenuNewGameIndex(int index, int scanCode)
{
	if (scanCode == SDL_SCANCODE_DOWN)
	{
		index = index + 2;
		if (index > 6)
			index = 6;
		return (index);
	}
	if (scanCode == SDL_SCANCODE_UP)
	{
		if (index == 6)
			return (5);
		index = index - 2;
		if (index == -1)
			index = 5;
		if (index == -2)
			index = 4;
		return (index);
	}
	if (scanCode == SDL_SCANCODE_LEFT)
	{
		index = index - 1;
		if (index == -1)
			index = 5;
		return (index);
	}
	if (scanCode == SDL_SCANCODE_RIGHT)
	{
		index = index + 1;
		if (index == 7)
			index = 6;
		return (index);
	}
	return(0);
}

static void eventMenuMain(u_int32_t *menuStep, SDL_KeyboardEvent *event, int *index)
{
	int newIndex;

	newIndex = readBits(4, *index);
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_ESCAPE)
			*menuStep = quitM;
		if (event->keysym.scancode == SDL_SCANCODE_BACKSPACE)
		{
			*menuStep = title;
			newIndex = 0;
		}
		if (event->keysym.scancode == SDL_SCANCODE_SPACE)
		{
			if (newIndex == 0)
				*menuStep = newGame;
			if (newIndex == 1)
				*menuStep = option;
			if (newIndex == 2)
				*menuStep = success;
			if (newIndex == 3)
				*menuStep = aboutMe;
			newIndex = 0;
		}
		if (event->keysym.scancode == SDL_SCANCODE_UP)
			newIndex = setMenuMainIndex(newIndex, SDL_SCANCODE_UP);
		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
			newIndex = setMenuMainIndex(newIndex, SDL_SCANCODE_DOWN);
	}
	*index = newIndex + 0X80;
}


static void eventMenuNewGame(u_int32_t *menuStep, SDL_KeyboardEvent *event, int *index)
{
	int i;
	int selection;

	i = readBits(4, *index);
	if ((*index & 0x80) == 0)
		selection = readBits(4, (*index >> 4));
	else
		selection = -1;
	if (selection > -1 && event->keysym.scancode > 78 && event->keysym.scancode < 83)
	{	
		i = selection;
		selection = -1;
	}
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_ESCAPE)
			*menuStep = quitM;
		if (event->keysym.scancode == SDL_SCANCODE_BACKSPACE)
		{
			*menuStep = mainmenu;
			i = 0;
		}
		if (event->keysym.scancode == SDL_SCANCODE_UP)
			i = setMenuNewGameIndex(i, SDL_SCANCODE_UP);
		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
			i = setMenuNewGameIndex(i, SDL_SCANCODE_DOWN);
		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
			i = setMenuNewGameIndex(i, SDL_SCANCODE_LEFT);
		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
			i = setMenuNewGameIndex(i, SDL_SCANCODE_RIGHT);
		if (event->keysym.scancode == SDL_SCANCODE_SPACE)
		{
			if (selection > -1 && i == 6)
			{
				*menuStep = lvl;
				*index = 0 + (selection << 4);
				return ;
			}
			selection = i;
			i = 6;
		}
	}
	if (selection == -1)
		selection = 0x08;
	*index = i + (selection << 4);
}

void checkEventMenu(u_int32_t *menuStep, int *index)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (*menuStep & title)
				eventMenuTitle(menuStep, event);
			else if (*menuStep & mainmenu)
				eventMenuMain(menuStep, &event.key, index);
			else if (*menuStep & newGame)
				eventMenuNewGame(menuStep, &event.key, index);
			else
				break;
		}
		else
			break;
	}
}

void checkEventIntro(e_bool *pass)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.scancode == SDL_SCANCODE_SPACE)
				*pass = TRUE;
			else
				break;
		}
		else
			break;
	}
}