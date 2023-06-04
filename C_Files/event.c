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

static int setMenuNewGameIndex(int index, int scanCode, int jump, int maxIndex)
{
	if (scanCode == SDL_SCANCODE_DOWN)
	{
		index = index + jump;
		if (index > maxIndex)
			index = maxIndex;
		return (index);
	}
	if (scanCode == SDL_SCANCODE_UP)
	{
		if (index == maxIndex)
			return (maxIndex - 1);
		index = index - jump;
		if (index == -1)
			index = maxIndex - 1;
		if (index == 0 - jump)
			index = maxIndex - jump;
		return (index);
	}
	if (scanCode == SDL_SCANCODE_LEFT)
	{
		index = index - 1;
		if (index == -1)
			index = maxIndex - 1;
		return (index);
	}
	if (scanCode == SDL_SCANCODE_RIGHT)
	{
		index = index + 1;
		if (index == maxIndex + 1)
			index = maxIndex;
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
	*index = newIndex + 0X880;
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
	if ((selection > -1 && event->keysym.scancode > 78 && event->keysym.scancode < 83) || selection == 6)
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
			i = setMenuNewGameIndex(i, SDL_SCANCODE_UP, 2, 6);
		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
			i = setMenuNewGameIndex(i, SDL_SCANCODE_DOWN, 2, 6);
		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
			i = setMenuNewGameIndex(i, SDL_SCANCODE_LEFT, 2, 6);
		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
			i = setMenuNewGameIndex(i, SDL_SCANCODE_RIGHT, 2, 6);
		if (event->keysym.scancode == SDL_SCANCODE_SPACE)
		{
			if (selection > -1 && i == 6)
			{
				*menuStep = lvl;
				*index = 0x800 + (selection << 4) + 0;
				return ;
			}
			selection = i;
			i = 6;
		}
	}
	if (selection == -1)
		selection = 0x08;
	*index = i + (selection << 4) + 0x800;
}

static void eventMenulvl(u_int32_t *menuStep, SDL_KeyboardEvent *event, int *index)
{
	int		i;

	i = readBits(4, *index);
	if (event->repeat == 0)
	{
		if (event->keysym.scancode == SDL_SCANCODE_ESCAPE)
			*menuStep = quitM;
		if (event->keysym.scancode == SDL_SCANCODE_BACKSPACE)
			*menuStep = newGame;
		if (event->keysym.scancode == SDL_SCANCODE_UP)
			i = setMenuNewGameIndex(i, SDL_SCANCODE_UP, 1, 3);
		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
			i = setMenuNewGameIndex(i, SDL_SCANCODE_DOWN, 1, 3);
		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
			i = setMenuNewGameIndex(i, SDL_SCANCODE_LEFT, 1, 3);
		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
			i = setMenuNewGameIndex(i, SDL_SCANCODE_RIGHT, 1, 3);
	}
	*index = i;
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
			else if (*menuStep & lvl)
				eventMenulvl(menuStep, &event.key, index);
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