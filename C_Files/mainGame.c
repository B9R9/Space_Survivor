#include "mainGame.h"

e_bool mainGame(SDL_Renderer *render)
{
	u_int32_t	gameStep;

	gameStep = menu;
	while(gameStep != quit)
	{
		switch(gameStep)
		{
			case (menu):
				if (mainMenu(render, &gameStep) == FAIL)
					return (FAIL);
		}
	}
	return (SUCCESS);
}