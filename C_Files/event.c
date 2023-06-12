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
		if (index > maxIndex)
			index = maxIndex;
		return (index);
	}
	return(0);
}

static void eventMenuMain(u_int32_t *menuStep, SDL_KeyboardEvent *event, u_int32_t *index)
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


static void eventMenuNewGame(u_int32_t *menuStep, SDL_KeyboardEvent *event, u_int32_t *index)
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
				// printf("Index value in event %d\n", *index);
				return ;
			}
			selection = i;
			i = 6;
		}
	}
	if (selection == -1)
		selection = 0x08;
	*index = 0x800 + (selection << 4) + i;
}

static void eventMenulvl(u_int32_t *menuStep, SDL_KeyboardEvent *event, u_int32_t *index)
{
	int		i;
	int		selection;
	int		shipSelection;

	selection = -1;
	i = readBits(4, *index);
	shipSelection = readBits(4, *index >> 4);
	if ((*index & 0x800) == 0)
		selection = readBits(4, (*index >> 8));
	if ((selection > -1 && event->keysym.scancode > 78 && event->keysym.scancode < 83) || selection == 3)
	{	
		i = selection;
		selection = -1;
	}
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
		if (event->keysym.scancode == SDL_SCANCODE_SPACE)
		{
			if (selection > -1 && i == 3)
			{
				// printf("	VALIDATE SELECTion = %d\n", selection);
				*menuStep = runGame;
				*index = (selection << 8) + (shipSelection << 4) + 0;
				return ;
			}
			selection = i;
			i = 3;
			// printf("	SELECTion = %d\n", selection);
		}

	}
	// printf("VALUE OF SELECTION in event before leave %d\n", selection);
	if (selection == -1)
		selection = 0x08;
	// printf("VALUE OF inde in event before leave %d || %d || %d || %d\n", (selection << 8) + (shipSelection << 4) + i,(selection << 8), (shipSelection << 4), i );
	*index = (selection << 8) + (shipSelection << 4) + i;
}

// static void eventInGame(u_int32_t *step, SDL_KeyboardEvent *event, u_int32_t *index)
// {
// 	(void)index;
// 	if (event->repeat == 0)
// 	{
// 		if (event->keysym.scancode == SDL_SCANCODE_ESCAPE)
// 			*step = quit;
// 		if (event->keysym.scancode == SDL_SCANCODE_UP)
// 			*step = quit;
// 		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
// 			*step = quit;
// 		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
// 			*step = quit;
// 		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
// 			*step = quit;
// 	}

// }

void checkEventMenu(u_int32_t *step, u_int32_t *index)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (*step & title)
				eventMenuTitle(step, event);
			else if (*step & mainmenu)
				eventMenuMain(step, &event.key, index);
			else if (*step & newGame)
				eventMenuNewGame(step, &event.key, index);
			else if (*step & lvl)
				eventMenulvl(step, &event.key, index);
			// else if (*step & 0x03)
			// 	eventInGame(step, &event.key, index);
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

static void keyDown(SDL_KeyboardEvent *event, t_move *direction)
{
    if (event->repeat == 0)
    {
        if (event->keysym.scancode == SDL_SCANCODE_UP)
            direction->up = 1;
        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
            direction->down = 1;
        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
            direction->left = 1;
        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
            direction->right = 1;
    }
}

static void keyUp(SDL_KeyboardEvent *event, t_move *direction)
{
    if (event->repeat == 0)
    {
        if (event->keysym.scancode == SDL_SCANCODE_UP)
            direction->up = 0;
        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
            direction->down = 0;
        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
            direction->left = 0;
        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
            direction->right = 0;
    }
}

void checkEventGame(u_int32_t *step, t_move *direction)
{
	(void)step;
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
			keyDown(&event.key, direction);
		else if (event.type == SDL_KEYUP)
			keyUp(&event.key, direction);
		else
			break;
	}
}