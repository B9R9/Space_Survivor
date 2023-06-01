#include "main.h"


int main(void)
{
	t_screen	screen;

	srand((time(NULL))); // avoir pour mettre dans une fonction
	if (newScreen(&screen) == FAIL)
		return (destroyScreen(&screen), EXIT_FAILURE);
	if (mainIntro(screen.render) == FAIL)
		return (destroyScreen(&screen), EXIT_FAILURE);
	if (mainGame(screen.render) == FAIL)
		return (destroyScreen(&screen), EXIT_FAILURE);
	destroyScreen(&screen);
	return (EXIT_SUCCESS);
}