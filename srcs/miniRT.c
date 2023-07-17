#include "../incs/minirt.h"

void	initialize(t_rt *rt);


int	main(int argc, char **argv)
{
	t_rt	*rt;

	(void) argv;
	rt = malloc(sizeof(t_rt));
	if (argc == 2)
	{
		// file_parsing(argv[1], rt);
		// printf("MAIN: %s coord: %f, %f & %f\n", rt->sc->light.id, rt->sc->light.coord.x, rt->sc->light.coord.y, rt->sc->light.coord.z);
        // printf("MAIN: %s ratio: %f\n",rt->sc->light.id, rt->sc->light.ratio);
        // printf("MAIN: %s coord: %f, %f, %f\n", rt->sc->cam.id, rt->sc->cam.coord.x, rt->sc->cam.coord.y, rt->sc->cam.coord.z);
        // printf("MAIN: %s ori: %f, %f, %f\n", rt->sc->cam.id, rt->sc->cam.ori.x, rt->sc->cam.ori.y, rt->sc->cam.ori.z);
        // printf("MAIN: %s FOV: %f\n", rt->sc->cam.id, rt->sc->cam.fov);
		// printf("number of objects: %d\n", number_objects(rt->sc->obj));
		make_window(rt);
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
