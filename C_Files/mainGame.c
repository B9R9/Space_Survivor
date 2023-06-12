#include "mainGame.h"

e_bool mainGame(SDL_Renderer *render)
{
	u_int32_t	gameStep;
	u_int32_t	menuStep;
	u_int32_t	index;

	gameStep = menu;
	menuStep = title;
	index = 0x880;
	while(gameStep != quit)
	{
		switch(gameStep)
		{
			case (menu):
				if (mainMenu(render, &gameStep, &index, &menuStep) == FAIL)
					return (FAIL);
			case (game):
				if (gameRun(render, index, &gameStep) == FAIL)
					return (FAIL);
				break;
		}
	}
	return (SUCCESS);
}