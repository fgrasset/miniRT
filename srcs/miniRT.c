#include "../incs/minirt.h"

void	initialize(t_rt *rt);


int	main(int argc, char **argv)
{
	if (ac == 2)
	{
		parsing(argv[1]);
	}
	else
		print_error("2 args needed");
 /*check if the given argument is in .rt*/

}

/* initialize the structure */
void	initialize(t_rt *rt)
{
	rt->win_h = 600;
	rt->win_w = 1000;
}

/*
Pour le parsing, faire un ft_atoi pour les double, un pour les vecteurs, ils exit si le format n'est pas correct
Puis GNL + slit + strcmp pour savoir comment les classer dans une futur struct ?

Ensuite j'imagine que pour placer un pixel, il faudra faire passer les infos par pleins de fonctions différentes
qui vont à chaqu fois modifier légèrement les données du pixel en fonctions d'autres paramètres.

Il faut apparemment plutôt utiliser des matrices de transformations

Idée pour les structures, en faire une par type d'élément.
Donc,t_camera, t_light, t_scenes, t_figures
Quoi que le gars a 25 struct wtf
*/
