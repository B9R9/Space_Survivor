#include "textureToList.h"


static void nextTile(int *xTile, int *yTile, int indexTexture, SDL_Texture *spriteSheet)
{
	int maxW, maxH;

	SDL_QueryTexture(spriteSheet, NULL, NULL, &maxW, &maxH);
	*xTile += maxW/g_textureParam[indexTexture].columnsSize;
	if (*xTile >= maxW)
	{
		*xTile = 0;
		*yTile += (maxH / g_textureParam[indexTexture].lineSize);
	}
}

static SDL_Rect newTile(SDL_Texture *texture, int textureIndex)
{
	int 		x, y;
	SDL_Rect	tile;

	SDL_QueryTexture(texture, NULL, NULL, &x, &y);
	tile.x = 0;
	tile.y = 0;
	tile.w = x / g_textureParam[textureIndex].columnsSize;
	tile.h = y / g_textureParam[textureIndex].lineSize;
	return (tile);
}

static SDL_Texture *newTexture(SDL_Texture *globaltexture,SDL_Renderer *render, SDL_Rect tile)
{
	int x, y;
	SDL_Texture *dest;

	SDL_QueryTexture(globaltexture, NULL, NULL, &x, &y);
	dest = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, x, y);
	if (dest == NULL)
		return (NULL);
	SDL_SetTextureBlendMode(dest, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(render, dest);
    SDL_RenderCopy(render, globaltexture, &tile, NULL); 
    SDL_SetRenderTarget(render, NULL);
	return (dest);
}

static void setNode(t_textureToLi **node, int id, SDL_Texture *spriteSheet, SDL_Renderer *render, SDL_Rect tile)
{
	(*node)->id = id;
	(*node)->sizeLi = 0;
	(*node)->next = NULL;
	(*node)->texture = newTexture(spriteSheet, render, tile);
	if ((*node)->texture == NULL)
	{
		free((*node));
		(*node) = NULL;
	}
}

static void	newNode(t_textureToLi **node, int id, SDL_Texture *spriteSheet, SDL_Renderer *render, SDL_Rect tile)
{
	(*node) = (t_textureToLi *)malloc(sizeof(t_textureToLi));
	if ((*node) == NULL)
		return;
	setNode(node, id, spriteSheet, render, tile);
}

static t_textureToLi *addNodeToLi(t_textureToLi *head, t_textureToLi *node)
{
	if (head == NULL)
		return (node);
	if (node == NULL)
		return (head);
	node->next = head;
	return (node);	
}

static t_textureToLi *newList(int indexTexture, SDL_Rect tile, SDL_Texture *spriteSheet, SDL_Renderer *render)
{
	t_textureToLi	*li;
	t_textureToLi	*node;
	int				maxElement;
	int				i;

	i = 0;
	li = NULL;
	node = NULL;
	maxElement = g_textureParam[indexTexture].totalElement;
	while (i < maxElement)
	{
		newNode(&node, i, spriteSheet, render, tile);
		node->sizeLi = maxElement;
		if (node == NULL)
			return (NULL);
		li = addNodeToLi(li, node);
		if (li == NULL)
			return (NULL);
		nextTile(&tile.x, &tile.y, indexTexture, spriteSheet);
		printf("--->%d %d %d %d\n", tile.x, tile.y, tile.w, tile.h);
		node = NULL;
		i++;
	}
	return (li);
}

t_textureToLi *newTextureLi(int indexTexture, SDL_Renderer *render)
{
	SDL_Texture		*spriteSheet;
	SDL_Rect		tile;
	t_textureToLi	*li;

	li = NULL;
	spriteSheet = imgToTexture(g_textureParam[indexTexture].path, render);
	if (spriteSheet == NULL)
		return (NULL);
	tile = newTile(spriteSheet, indexTexture);
	li = newList(indexTexture,tile, spriteSheet, render);
	if (li == NULL)
		return (SDL_DestroyTexture(spriteSheet), NULL);
	SDL_DestroyTexture(spriteSheet);
	return (li);
}

void cleanLiOfTexture(t_textureToLi *li)
{
	t_textureToLi *toDelete;

	toDelete = NULL;
	while (li != NULL)
	{
		toDelete = li;
		li = li->next;
		toDelete->next = NULL;
		toDelete->id = 0;
		toDelete->sizeLi = 0;
		SDL_DestroyTexture(toDelete->texture);
		free(toDelete);
		toDelete = NULL;
	}
}