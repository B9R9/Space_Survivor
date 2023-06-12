#include "utilsSDL.h"

/*
**  @size: Taille de la police
**  @fontIndex: donne l index de la police dans le tableau fontArray(param.h)
**  Load la police
*/
TTF_Font *set_font(int size, int fontIndex)
{
    return (TTF_OpenFont(fontArray[fontIndex], size));
}

SDL_Texture *createTextureFromText(const char *text, int fontIndex, size_t size,\
	const char *color, SDL_Renderer *render)
{
	SDL_Texture *texture;
	SDL_Surface *surface;

	surface = createSurfaceFromText(text, fontIndex, size, hexConverter(color));
	if (surface == NULL)
		return (NULL);
	texture = createTextureFromSurface(surface, render);
	if (texture == NULL)
		return (SDL_FreeSurface(surface), NULL);
	SDL_FreeSurface(surface);
	return (texture);
}

SDL_Surface *createSurfaceFromText(const char *text, int fontIndex, size_t size, u_int32_t colorValue)
{
	SDL_Surface *surface;
	TTF_Font	*font1;
	SDL_Color	color;

	font1 = set_font(size, fontIndex);
	color = colorConverter(colorValue, 255);
	surface = TTF_RenderText_Blended(font1, text, color);
	if (surface == NULL)
		return (errPrint("createSurfaceFromText", SDL_GetError()), NULL);
	if (SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0, 0)) != 0)
	{
		SDL_FreeSurface(surface);
		TTF_CloseFont(font1);
		return (errPrint("createSurfaceFromText", SDL_GetError()), NULL);
	}
    TTF_CloseFont(font1);
    return (surface);
}

/*
**  @render: Affichage
**  @surf:  Surface a convertir
**  Converti une surface en texture et return la dite texture.
*/
SDL_Texture *createTextureFromSurface(SDL_Surface *surf, SDL_Renderer *render)
{
	SDL_Texture	*temp;
	SDL_Texture	*texture;

	temp = SDL_CreateTextureFromSurface(render, surf);
	if (temp == NULL)
		return (errPrint("createTextureFromSurface", SDL_GetError()), NULL);
	texture = SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, surf->w, surf->h);
	if (texture == NULL)
	{
		SDL_DestroyTexture(temp);
		return (errPrint("createTextureFromSurface", SDL_GetError()), NULL);
	}
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(render, texture); /* La cible de rendu est maintenant texture. */
	SDL_RenderCopy(render, temp, NULL, NULL); /* On copie tmp sur texture */
	SDL_SetRenderTarget(render, NULL); /* La cible de rendu est de nouveau le renderer. */
	SDL_DestroyTexture(temp);
	return (texture);
}

/*
**	@file: PATH vers file
**	load une image dans une surface
*/
SDL_Surface *imgToSurface(const char *file)
{
	SDL_Surface *surface;
	
	surface = IMG_Load(file);
	if (surface == NULL)
		return (errPrint("imgToSurface", SDL_GetError()), NULL);
	return (surface);
}

/*
**	@file: PATH vers file
**	@render: Affichage
**	load une image dans une texture
*/
SDL_Texture *imgToTexture(const char *file, SDL_Renderer *render)
{
	SDL_Surface	*surface;
	SDL_Texture	*texture;

	texture = NULL;
	surface = imgToSurface(file);
	if (surface == NULL)
		return (texture);
	texture = createTextureFromSurface(surface, render);
	SDL_FreeSurface(surface);
	return (texture);
}

/*
**	@render: Affichage
**	reset l affichage a un ecran noir
*/
void clearRender(SDL_Renderer *render)
{
	SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
	SDL_RenderFillRect(render, NULL);
}

/*
**	@texture: texture a afficher
**	@render: rendu
**	Affiche la globalite de la texture dans le render
*/
void fullCopyTextureInRender(SDL_Texture *texture, SDL_Renderer *render)
{
	SDL_RenderCopy(render, texture, NULL, NULL);
}

/**
 * @brief Affiche le render
 * 
 * @param render: rendu
 */
void displayRender(SDL_Renderer *render)
{
	SDL_RenderPresent(render);
}

/**
 * @brief Affiche une texture dans le SDL_Rect passe en parametre
 * 
 * @param render : rendu
 * @param texture : Texture a afficher 
 * @param container : SDL_Rect ou afficher la texture
 */
void copyTextureInRenderWithRect(SDL_Renderer *render, SDL_Texture *texture, SDL_Rect container)
{
    SDL_RenderCopy(render, texture, NULL, &container);
}

/*
**	hexValue : hexadecimal value
**	alphavalue: valeur de l alpha
**	Convertir une couleur au formet hexadecimal en SDL_Color
*/
SDL_Color colorConverter(u_int32_t hexValue, int alphaValue)
{
  SDL_Color color;
  color.r = ((hexValue & 0xFF0000) >> 16);  // Extract the RR byte
  color.g = ((hexValue & 0xFF00) >> 8) ;   // Extract the GG byte
  color.b = ((hexValue & 0xFF)) ;        // Extract the BB byte
  color.a = alphaValue;
  return (color); 
}

/**
 * @brief Convertir un char * de type hexadecimal en valeur numerique
 * 
 * @param hexvalue : char *hexdecimal value
 * @return u_int32_t: la conversion du char * en u_int32_t
 */
u_int32_t hexConverter(const char *hexvalue)
{
    char hexDigits[16] = { '0', '1', '2', '3', '4', '5', '6', '7',\
                           '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    u_int32_t ret;
    int  i, j, power;

    ret = 0;
    power = 0;
    i = 0;
    i = strlen(hexvalue) -1;
    while (0 <= i)
    {
        j = 0;
        while (j < 16)
        {
            if (hexvalue[i] == hexDigits[j])
                ret += j * pow(16, power);
            j++;
        }
        power++;
        i--;
    }
    return (ret);
}

/**
 * @brief Create a SDL_Rect object
 * 
 * @param x : abscisse
 * @param y :ordonne 
 * @param w :width
 * @param h :heigth
 * @return SDL_Rect : le containeur au dimension 
 */
SDL_Rect createRect(int x, int y, int w, int h)
{
	SDL_Rect    container;

	container.x = percent(SCREEN_W, x);
	container.y = percent(SCREEN_H, y);
	container.w = percent(SCREEN_W, w);
	container.h = percent(SCREEN_H, h);
	return (container);
}


/**
 * @brief Set the color 
 * 
 * @param hexValue: char * Hex value 
 * @param alphaValue*: the alpha value(opacity) desire 
 * @param render: rendu 
 */
void    toColor(const char *hexValue,int alphaValue, SDL_Renderer *render)
{
    SDL_Color color;
    color = colorConverter(hexConverter(hexValue), alphaValue);
    SDL_SetRenderDrawColor(render, color.r, color.g, color.b, color.a);
}

/**
 * @brief copy a SDL RECT to render, You can fill the rectangle or not
 * and select the color
 * option 0: draw line only
 * option 1: fill the rect
 * 
 * @param rect : SDL_Rect to copy
 * @param fillRect: option to fill or not 
 * @param render: rendu 
 * @param color: char * hexvalue 
 * @param alphaValue : opacity
 */
void copyRectInRender(SDL_Rect rect, int options, SDL_Renderer *render, char *color, int alphaValue)
{
	toColor(color, alphaValue, render);
	if (options == 0)
		SDL_RenderDrawRect(render, &rect);
	if (options == 1)
		SDL_RenderFillRect(render, &rect);	
}

void drawContour(char *color, int alphaValue, SDL_Rect rect, SDL_Renderer *render)
{
	toColor(color, alphaValue, render);
	SDL_RenderDrawRect(render, &rect);
}

SDL_Rect defineRect(int x, int y, int w, int h)
{
	SDL_Rect	temp;

	temp.x = x;
	temp.y = y;
	temp.w = w;
	temp.h = h;
	return (temp);
}