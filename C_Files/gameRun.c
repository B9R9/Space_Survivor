#include "gameRun.h"

static e_bool loopGame(u_int32_t gameStep)
{
	if (gameStep == menu)
		return (FALSE);
	if (gameStep == quit)
		return (FALSE);
	return (TRUE);
}

// static int maxHeight(SDL_Texture *texture)
// {
// 	int	height;

// 	SDL_QueryTexture(texture, NULL, NULL, NULL, &height);
// 	return (height);
// }

// static void animBackground(SDL_Renderer *render, SDL_Texture *background, int *index)
// {
// 	int			maxTextureW;
// 	int			maxTextureH;
// 	SDL_Rect	src;
// 	SDL_Rect	dst;


// 	SDL_QueryTexture(background, NULL, NULL, &maxTextureW, &maxTextureH);
// 	if (*index >= maxTextureW)
// 		*index = 0;
// 	src = defineRect(*index, 0, 5, maxTextureH);
// 	dst = defineRect(-1, 0, 5, SCREEN_H);
// 	while (dst.x < SCREEN_W)
// 	{
// 		SDL_RenderCopy(render, background, &src, &dst);
// 		src.x += 2;
// 		if (src.x >= maxTextureW)
// 			src.x = 0;
// 		dst.x += 2;
// 	}
// 	*index += 2;
// }

static t_textureToLi *animBackgroundV2(SDL_Renderer *render, SDL_Texture *background)
{
	t_textureToLi	*new;
	t_textureToLi	*node;
	t_textureToLi	*temp;
	int			maxTextureW;
	int			maxTextureH;
	int			sizeLi;
	int			index;
	int			speed;
	SDL_Rect	src;
	SDL_Rect	dst;

	new = NULL;
	node = NULL;
	sizeLi = 0;
	index = 0;
	speed = 5;
	SDL_QueryTexture(background, NULL, NULL, &maxTextureW, &maxTextureH);
	while (index <= maxTextureW)
	{
		node = (t_textureToLi *)malloc(sizeof(t_textureToLi));
		if (node == NULL)
			EXIT_FAILURE;
		src = defineRect(index, 0, speed, maxTextureH);
		dst = defineRect(-1, 0, speed, SCREEN_H);
		node->texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, SCREEN_W, SCREEN_H);
		SDL_SetTextureBlendMode(node->texture, SDL_BLENDMODE_BLEND);
		SDL_SetRenderTarget(render, node->texture);
		node->id = index;
		while (dst.x < SCREEN_W)
		{
			SDL_RenderCopy(render, background, &src, &dst);
			src.x += speed;
			if (src.x >= maxTextureW)
				src.x = 0;
			dst.x += speed;
		}
		SDL_SetRenderTarget(render, NULL);
		index += speed;
		sizeLi += 1;
		node->sizeLi = sizeLi;
		node->next = NULL;
		if (new == NULL)
			new = node;
		else
		{
			temp = new;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = node;
		}
	}
	temp = new;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
	return (new);
}

static void buildBackground(t_game *data, SDL_Renderer *render)
{
	// animBackground(render,data->background, &data->indexBackground);
	data->backgroundView = animBackgroundV2(render,data->background);
	/*build le fond avant de mettre le player, le shooting ou ennemie*/
}

static void loadGame(t_game *data, int indexLvl, SDL_Renderer *render)
{
	data->background = imgToTexture(g_LvlData[indexLvl].backgroundPath, render);
	data->gamePart = 0x03;
	data->indexBackground = 0;
	buildBackground(data, render);
	data->direction.down = 0;
	data->direction.up = 0;
	data->direction.left = 0;
	data->direction.right = 0;
}

e_bool gameRun(SDL_Renderer *render, u_int32_t param, u_int32_t *gameStep)
{
	(void) gameStep;
	t_player	player;
	t_game		data;
	t_timer		fps;
	int ship;
	int lvl;

	printf("*******************************************\n");
	ship = readBits(4, param >> 4);
	lvl = readBits(4, param >> 8);
	newPlayer(&player, ship);
	printf("GAME SECTION: Check passage player created\n");
	loadGame(&data, lvl, render);
	printf("GAME SECTION: Check passage game data loaded\n");
	while(loopGame(*gameStep))
	{
		// printf("GAME SECTION: Check passage game start loop\n");
		startTimer(&fps.start);
		clearRender(render);
		checkEventGame(gameStep, &data.direction);
		printf(" %d || %d || %d || %d\n", data.direction.up, data.direction.down, data.direction.left, data.direction.right );
		// printf("GAME SECTION: Check passage game event checked\n");
		// buildBackground(&data, render);
		SDL_RenderCopy(render, data.backgroundView->texture, NULL, NULL);
		data.backgroundView = data.backgroundView->next;
		playerPosition(render, &player, data.direction);
		// printf("GAME SECTION: Value index --> %d\n", data.indexBackground);
		// printf("GAME SECTION: Check passage game background builded\n");
		displayRender(render);
		setDelta(&fps.delta, fps.start);
		setDelay(fps.delta, 33);
		// printf("GAME SECTION: Check passage game end loop\n");
	}

	printf("GAME SECTION: Your ship is %d \n", ship);
	printf("GAME SECTION: Your lvl is %d \n", lvl);
	return (FAIL);
}