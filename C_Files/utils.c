#include "utils.h"

/*
**	@location: fonction ou l erreur se trouve
**	@error: error type(from SDL_GetError())
**	Display error messages in STDERR
*/
void errPrint(const char *location, const char *error)
{
	fprintf(stderr, "In %s : %s\n", location, error);
}

/**
 * @brief Compare gamePart avec location de la boucle
 * 
 * @param gameSteps: bitflags pour suivre les etapes du jeu
 * @return e_bool: a boolean
 */
e_bool run(u_int32_t gameSteps)
{
	if (gameSteps & 0x40)
		return (FALSE);
	return (TRUE);
}

/**
 * @brief Calcule la value suivant un pourcentage de la totalite
 * 
 * @param total : value total == 100% (exprime digit)
 * @param value : valeur souhaite (exprime en %) 
 * @return int : traduit le value(%) en digit
 */
int percent(int total, int value)
{
    return ((value * total) / 100);
}

int	randomnbr(int min, int max)
{
	int	nbr = 0;
	nbr = (rand() % ((max - min + 1)) + min);
	return (nbr);
}

void setBackground(SDL_Texture *background, SDL_Renderer *render)
{
	SDL_RenderCopy(render, background, NULL, NULL);
}

/**
 * @brief extraire une valeur pour un certain nombre de bits
 * 
 * @param nbBits : total bit a lire
 * @param value : looking bits inside 
 * @return int : la valeur suivant les nombre bits lue
 */

int readBits(int nbBits, int value)
{
	int i;
	int mask;

	i = 1;
	mask = 0;
	while (i <= nbBits)
	{
		mask += i;
		i = i * 2;
	}
	return (value & mask);
}
