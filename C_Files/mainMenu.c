#include "mainMenu.h"

/**
 * @brief Charge dans une struct les donnees pour affichage
 * de la partie titre
 * 
 * @param param  struct contenant tous les textures necessaires pour l affichage de la partie titre
 * @param render rendu
 * @return e_bool: boolean pour verifier le succes de la fonction
 */
static e_bool loadTitleParam(t_menuTitle *param, SDL_Renderer *render)
{
	param->background = imgToTexture(BACKGROUND, render);
	if (param->background == NULL)
		return (FAIL);
	param->titre = createTextureFromText("SPACE SURVIVOR", PRSTART, 30, YELLOW, render);
	if (param->titre == NULL)
		return (FAIL);
	param->sousTitre = createTextureFromText("Insert Coin or Press Space to continue", PRSTART, 20, WHITE, render);
	if (param->sousTitre == NULL)
		return (FAIL);
	param->exit = createTextureFromText("Press ESC to quit", PRSTART, 20, WHITE, render);
	if (param->exit == NULL)
		return (FAIL);
	param->timeCounter = 0;
	param->asteroid_t = newTextureLi(ASTEROID, render);
	if (param->asteroid_t == NULL)
		return (errPrint("newTextureLi", "Fail to create list"), FAIL);
	param->asteroid_l = NULL;
	param->impact_t = newTextureLi(IMPACT, render);
	if (param->impact_t == NULL)
		return (errPrint("newTextureLi", "Fail to create list"), FAIL);
	return (SUCCESS);
}

static e_bool loadMenuWithColor(t_menuMain_D *menu, const char *color, SDL_Renderer *render)
{
	menu->newGame_t = createTextureFromText("New Game", PRSTART, 30, color, render);
	if (menu->newGame_t == NULL)
		return (FAIL);
	menu->options_t = createTextureFromText("Options", PRSTART, 30, color, render);
	if (menu->options_t == NULL)
		return (FAIL);
	menu->success_t = createTextureFromText("Success", PRSTART, 30, color, render);
	if (menu->success_t == NULL)
		return (FAIL);
	menu->aboutMe_t = createTextureFromText("About me", PRSTART, 30, color, render);
	if (menu->aboutMe_t == NULL)
		return (FAIL);
	return (SUCCESS);
}

static e_bool loadMainParam(t_menuMain *param, SDL_Renderer *render)
{
	if (loadMenuWithColor(&param->menuRed, RED, render) == FAIL)
		return (errPrint("loadMainParam", "Error loading texture menuRed"), FAIL);
	if (loadMenuWithColor(&param->menuYellow, YELLOW, render) == FAIL)
		return (errPrint("loadMainParam", "Error loading texture menuYellow"), FAIL);
	param->background = imgToTexture(BACKGROUND, render);
	if (param->background == NULL)
		return (FAIL);
	param->exit = createTextureFromText("Press ESC to quit", PRSTART, 20, WHITE, render);
	if (param->exit == NULL)
		return (FAIL);
	param->titre = createTextureFromText("SPACE SURVIVOR", PRSTART, 30, YELLOW, render);
	if (param->titre == NULL)
		return (FAIL);
	param->transition = FAIL;
	param->index = 0;
	return (SUCCESS);
}

static e_bool loadNewGameParam(t_menuNewGame *param, SDL_Renderer *render)
{
	param->background = imgToTexture(BACKGROUND, render);
	if (param->background == NULL)
		return (FAIL);
	param->rogue1 = createRect(52, 27, 5, 4);
	// param->rogue1 = imgToTexture(ROGUE1, render);
	// if (param->rogue1 == NULL)
	// 	return (FAIL);
	param->selectionShipText = createTextureFromText("Select your ship", PRSTART, 30, WHITE, render);
	if (param->selectionShipText == NULL)
		return (FAIL);
	param->notAvailable = createTextureFromText("Not Available", PRSTART, 30, WHITE, render);
	if (param->notAvailable == NULL)
		return (FAIL);
	return (SUCCESS);	
}
/**
 * @brief Dispatcher vers les differentes struct a charger
 * 
 * @param param: Struct contenant les textures necessaire 
 * @param render: rendu 
 * @return e_bool: boolean pour determiner le succes ou lechec d ela function 
 */
static e_bool loadMenu(t_menuParam *param, SDL_Renderer *render)
{
	if (loadTitleParam(&param->title, render) == FAIL)
		return (FAIL);
	if (loadMainParam(&param->main, render) == FAIL)
		return (FAIL);
	if (loadNewGameParam(&param->new, render) == FAIL)
		return (FAIL);
	param->index = 0X80;	
	return (SUCCESS);
}

/**
 * @brief Dispacht vers les differents menu du jeu
 * 
 * @param menuStep:  
 * @param render : rendu
 */
static void dispachtMenu(u_int32_t   *menuStep,SDL_Renderer *render, t_menuParam *param,\
	t_timer fps)
{
	if (*menuStep & title || *menuStep & transition)
		displayTitle(&param->title, render, fps, menuStep);
	else if (*menuStep & mainmenu)
		displayMain(&param->main, render, param->index);
	else if (*menuStep & newGame)
		displayNewGame(&param->new, render, menuStep, &param->index);
	else if (*menuStep & lvl)
		printf ("lvl\n");
	else if (*menuStep & option)
		printf ("options\n");
	else if (*menuStep & success)
		printf ("success\n");
	else if (*menuStep & aboutMe)
		printf ("aboutMe\n");
}

/**
 * @brief Boucle principale pour la gestion des menus 
 * 
 * @param render : rendu
 * @param gameStep: bitflags qui suit l evolution dans le jeu 
 */
e_bool mainMenu(SDL_Renderer *render, u_int32_t *gameStep)
{
	t_menuParam menuT;
	t_timer		fps;
	u_int32_t	menuStep;

	menuStep = title;
	if (loadMenu(&menuT, render) == FAIL)
		return (FAIL);
	while (run(menuStep))
	{
		startTimer(&fps.start);
		clearRender(render);
		setBackground(menuT.title.background, render);
		copyTextureInRenderWithRect(render,menuT.title.titre, createRect(5, 28, 90, 11));
		checkEventMenu(&menuStep, &menuT.index);
		dispachtMenu(&menuStep, render, &menuT, fps);
		displayRender(render);
		setDelta(&fps.delta, fps.start);
		setDelay(fps.delta, 33);
	}
	if (menuStep & quitM)
		*gameStep = quit;
	return (SUCCESS);
}