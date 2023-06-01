#include "fonduAnim.h"

/*
**	@render: Affichage
**	@texture: la texture a afficher
**	@stime: duration de l effent en seconde
**	->SDL_SetTextureAlphaMod permet de modifier la valeur alpha de la Texture en parametre
**	Cree une animation fondu au jour de la duree stime
**	->la valeur 255 correspond au max de la value Alpha
**	-> 33 est le nombe en milliseconde pour l affichage d une image (1000 / 30)
*/
void fonduAuNoir(SDL_Renderer *render, SDL_Texture *texture, double stime)
{
	t_timer	fps;
	int		opacity;
	e_bool 	pass;
	int		x;

	x = 255 /((stime * 1000) / 33);
	opacity = 255;
	pass = FALSE;
	while (opacity > 0)
	{
		startTimer(&fps.start);
		checkEventIntro(&pass);
		if (pass)
			break;
		clearRender(render);        
		SDL_SetTextureAlphaMod(texture, opacity);
		fullCopyTextureInRender(texture, render);
		displayRender(render);
		opacity -= x;
		setDelta(&fps.delta, fps.start);
		setDelay(fps.delta, 33);
	}
}

void fonduAuJour(SDL_Renderer *render, SDL_Texture *texture, double stime)
{
	t_timer	fps;
	e_bool	pass;
	int		opacity;
	int		x;

	x = 255 /((stime * 1000) / 33);
	opacity = 0;
	pass = FALSE;
	while (opacity < 255)
	{
		startTimer(&fps.start);
		clearRender(render);        
		SDL_SetTextureAlphaMod(texture, opacity);
		fullCopyTextureInRender(texture, render);
		displayRender(render);
		opacity += x;
		setDelta(&fps.delta, fps.start);
		setDelay(fps.delta, 33);
		checkEventIntro(&pass);
		if (pass)
			break;
	}
}
