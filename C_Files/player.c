#include "player.h"

void newPlayer(t_player *newPlayer, int shipIndex)
{
	newPlayer->color = g_spaceShipArr[shipIndex].color;
	newPlayer->live = 100;
	/*regRDER UNE declaration en 1 ligne ou fair eune fonction pour set le spawn*/
	newPlayer->position.x = percent(SCREEN_W, 15);
	newPlayer->position.y = percent(SCREEN_H, 40);
	newPlayer->position.w = percent(SCREEN_W, 10);
	newPlayer->position.h = percent(SCREEN_W, 4);
}

void playerPosition(SDL_Renderer *render, t_player *player, t_move direction)
{
	SDL_Rect pos;
	if (direction.up)
		player->position.y -= 7;
	if (direction.down)
		player->position.y += 7;
	if (direction.left)
		player->position.x -= 8;
	if (direction.right)
		player->position.x += 6;
	pos = defineRect(player->position.x, player->position.y, player->position.w, player->position.h);
	copyRectInRender(pos, 1, render, player->color, 255);
}