#include "timer.h"

void startTimer(int *start)
{
	*start = (int)SDL_GetTicks();
}

void setDelta(int *delta, int start)
{
	*delta = (int)SDL_GetTicks() - start;
}

void setDelay(int delta, int target)
{
	int diff;

	diff = 0;
	if (delta < target)
	{
		diff = (target - delta) - 1;
		SDL_Delay(diff);
	}
	printf("SDL_DELAY ---> %d\n", diff);
}

