#include "animAsteroid.h"

static t_element *addNodeToLi(t_element *head, t_element *node)
{
	if (node == NULL)
		return (head);
	if (head == NULL && node)
		return (node);
	node->next = head;
	return (node);	
}

/**
 * @brief define a point between 1 and SCREEN_W + SCREEN_H
 * 
 * @param max: max value
 * @return int: a nbr between 1 and max 
 */
static int findSpawn(int max)
{
	return (randomnbr(1, max));
}

static SDL_Texture *setTexture(t_textureToLi *asteroid_t)
{
	int				index;
	int				max;
	int				i;
	t_textureToLi	*temp;

	temp = NULL;
	i = 0;
	max = asteroid_t->sizeLi;
	index = randomnbr(1, max);
	temp = asteroid_t;
	while (temp != NULL)
	{
		if (index == i)
			return (temp->texture);
		i++;
		temp = temp->next;
	}
	return (NULL);
}


/**
 * @brief Set the starting point of asteroid.
 * 
 * @return SDL_Rect: the position 
 */
static SDL_Rect	setPosition(void)
{
	SDL_Rect pos;

	pos.x = findSpawn(SCREEN_W + SCREEN_H);
	pos.y = -10;
	pos.w = 20;
	pos.h = 20;
	if (pos.x > SCREEN_W)
	{
		pos.y = pos.x - SCREEN_W;
		pos.x = SCREEN_W + 1;
	}
	return (pos);
}

static void setElement(t_element **node, t_textureToLi *asteroid_t)
{
	(*node)->position = setPosition();
	(*node)->texture = setTexture(asteroid_t);
	(*node)->speed = randomnbr(1, 5);
	(*node)->angle = randomnbr(1, 5);
	(*node)->rotate = 0.0f;
	(*node)->speedRotate = (float)randomnbr(1, 10);
	(*node)->indexAnim = -1;
	(*node)->timeAnim = 0;
	(*node)->next = NULL;
}

static e_bool newElement(t_element **new, t_textureToLi *asteroid_t)
{
	(*new) = (t_element *)malloc(sizeof(t_element));
	if ((*new) == NULL)
		return (FAIL);
	setElement(new, asteroid_t);
	if ((*new) == NULL)
		return (errPrint("setElement AnimAsteroid", "Fail to set Element"), FAIL);
	return (SUCCESS);
}

static void freeNode(t_element *node)
{
	free(node);
	node = NULL;
}

e_bool   outOfScreen(SDL_Rect position)
{
    if (position.x > SCREEN_W || position.x < -10)
        return (TRUE);
    if (position.y > SCREEN_H || position.y < -10)
        return (TRUE);
    return (FALSE);
}

static t_element *removeOutOfPosition(t_element *li)
{
	t_element	*prev;
	t_element	*temp;
	t_element	*remove;

	if (li == NULL)
		return (NULL);
	temp = li;
	prev = NULL;
	remove = NULL;
	while (temp != NULL)
	{
		if (outOfScreen(temp->position))
		{
			if (prev == NULL)
			{
				remove = temp;
				free(remove);
				remove = NULL;
				temp = temp->next;
				li = temp;
			}
			else
			{
				prev->next = temp->next;
				temp->next = NULL;
				if (temp)
					freeNode(temp);
				temp = prev->next;
			}
		}
		else
		{
			prev = temp;
			temp = temp->next;
		}
	}
	return (li);
}

/**
 * @brief update the position, and the rotation, and the animatiotime for every asteroid
 * 
 * @param asteroid: list of all element
 * @param deltaTime: time between 2 loops
 */
static void updateAsteroidPosition(t_element **asteroid, int deltaTime)
{
	t_element	*temp;

	temp = (*asteroid);
	while (temp != NULL)
	{
		if (temp->indexAnim == -1)
		{
			temp->position.x -= temp->angle;
			temp->position.y += temp->speed;
			temp->rotate += temp->speedRotate;
			if (temp->rotate >= 360)
				temp->rotate = 0;
		}
		temp->timeAnim += deltaTime;
		temp = temp->next;
	}
	(*asteroid) = removeOutOfPosition((*asteroid));
}

/**
 * @brief Update the render and to a rotation of the asteroid
 * 
 * @param render : rendu
 * @param li: liste of element 
 */
void updateRender(SDL_Renderer *render, t_element *li)
{
    t_element *temp;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    temp = li;

    while (temp != NULL)
    {
        if (temp->indexAnim == -1)
            SDL_RenderCopyEx(render, temp->texture, NULL, &temp->position, temp->rotate, NULL, flip);
        temp = temp->next;
    }
}

static e_bool isImpact(t_element *asteroid_l, SDL_Rect pos,SDL_Rect colisionBoxTitle2, SDL_Rect colisionBoxExit, SDL_Rect colisionBoxTitle1)
{
	t_element	*temp;
	SDL_Rect	result;

	temp = asteroid_l; 
	if (SDL_IntersectRect(&colisionBoxExit, &pos, &result))
		return (TRUE);
	if (SDL_IntersectRect(&colisionBoxTitle1, &pos, &result))
		return (TRUE);
	if (SDL_IntersectRect(&colisionBoxTitle2, &pos, &result))
		return (TRUE);
	while (temp != NULL)
	{
		if (temp->position.x == pos.x && temp->position.y == pos.y)
			return (FALSE);
		if (SDL_IntersectRect(&temp->position, &pos, &result))
			return (TRUE);
		temp = temp->next;
	}
	return (FALSE);
}

/**
 * @brief Remove element who has been destroy
 * 
 * @param li: liste des elements a verifier 
 * @return t_element*: return la liste free des elements non necessaire
 */
static t_element *removeDestroy(t_element *li)
{
	t_element	*prev;
	t_element	*temp;
	t_element	*remove;

	if (li == NULL)
		return (NULL);
	temp = li;
	prev = NULL;
	remove = NULL;
	while (temp != NULL)
	{
		if (temp->indexAnim > 6)
		{
			if (prev == NULL)
			{
				remove = temp;
				free(remove);
				remove = NULL;
				temp = temp->next;
				li = temp;
			}
			else
			{
				prev->next = temp->next;
				temp->next = NULL;
				if (temp)
					freeNode(temp);
				temp = prev->next;
			}
		}
		else
		{
			prev = temp;
			temp = temp->next;
		}
	}
	return (li);
}

/**
 * @brief Verifie si temp->position est en colision avec les parametres
 * 
 * @param asteroid_l: liste des elements a verifier pour colision
 * @param impact_l: liste des textures impacts  
 * @param render: rendu 
 */
static void checkImpact(t_element **asteroid_l, t_textureToLi *impact_l, SDL_Renderer *render)
{
	t_element		*temp;
	t_textureToLi	*tempo;
	SDL_Rect		colisionBoxTitle1;
	SDL_Rect		colisionBoxTitle2;
	SDL_Rect		colisionBoxExit;

	temp = (*asteroid_l);
	colisionBoxTitle1 = createRect(5, 28, 31, 10);
	colisionBoxTitle2 = createRect(44, 28, 50, 10);
	colisionBoxExit = createRect(73, 95, 25, 2);
	while (temp != NULL)
	{
		if (isImpact((*asteroid_l), temp->position,colisionBoxTitle2, colisionBoxExit, colisionBoxTitle1) && temp->indexAnim == -1)
			temp->indexAnim = 0;
		if (temp->indexAnim >= 0 && temp->indexAnim < 7)
		{
			tempo = impact_l;
			while (tempo != NULL)
			{
				if (tempo->id == temp->indexAnim)
					break;
				tempo = tempo->next;
			}
			SDL_RenderCopy(render,tempo->texture, NULL, &temp->position);
			if (temp->timeAnim >70)
			{
				temp->indexAnim++;
				temp->timeAnim = 0;
			}
		}
		temp = temp->next;
	}
	(*asteroid_l) = removeDestroy((*asteroid_l));
}
/**
 * @brief Set la value indexAnim a 0, 
 * pour permettre de lancer l animation impact lors de la transition vers menumain
 * 
 * @param li: liste de tous les elements asteroids
 */
static void destroyAll(t_element **li)
{
	t_element	*temp;

	temp = (*li);
	while (temp != NULL)
	{
		if (temp->indexAnim == -1)
			temp->indexAnim = 0;
		temp = temp->next;
	}
}

/**
 * @brief Effectue l animation des asteroids sur le titre
 * 
 * @param asteroid_t: liste des textures des asteroids
 * @param asteroid_l; liste des asteroids cree
 * @param render: rendu
 * @param deltaTime: time between two loop
 * @param impact_t: liste des textures pour animation impact
 */
e_bool animAsteroid(t_textureToLi *asteroid_t, t_element **asteroid_l, SDL_Renderer *render,\
					 int deltaTime, t_textureToLi *impact_t)
{
	t_element	*new;
	static int time;

	new = NULL;
	time += deltaTime;
	if (time >= 1000 && deltaTime != 1033)
	{
		if (newElement(&new, asteroid_t) == FAIL)
			return (errPrint("animAsteroid", "Creation of a new element"), FAIL);
		(*asteroid_l) = addNodeToLi((*asteroid_l), new);
		if ((*asteroid_l) == NULL)
			return (errPrint("animAsteroid", "Adding Node to list"), FAIL);
		time = 0;
	}
	if (deltaTime == 1033)
	{
		deltaTime = 33;
		destroyAll(asteroid_l);
	}
	updateAsteroidPosition(asteroid_l, deltaTime);
	checkImpact(asteroid_l, impact_t, render);
	updateRender(render, (*asteroid_l));
	return (SUCCESS);
}
