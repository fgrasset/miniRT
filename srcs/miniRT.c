#include "../incs/minirt.h"

void	initialize(t_rt *rt);


int	main(int argc, char **argv)
{
	t_rt	*rt;

	(void) argv;
	rt = ft_calloc(sizeof(t_rt), 1);
	if (argc == 2)
	{
		file_parsing(argv[1], rt);
		printf("MAIN: %s ratio: %f\n", rt->sc->amb.id, rt->sc->amb.ratio);
		printf("MAIN: %s colors: %d, %d, %d\n",rt->sc->amb.id, rt->sc->amb.color.r, rt->sc->amb.color.g, rt->sc->amb.color.b);
		printf("MAIN: %s coord: %f, %f & %f\n", rt->sc->light.id, rt->sc->light.coord.x, rt->sc->light.coord.y, rt->sc->light.coord.z);
		printf("MAIN: %s ratio: %f\n",rt->sc->light.id, rt->sc->light.ratio);
		printf("MAIN: %s coord: %f, %f, %f\n", rt->sc->cam.id, rt->sc->cam.coord.x, rt->sc->cam.coord.y, rt->sc->cam.coord.z);
		printf("MAIN: %s ori: %f, %f, %f\n", rt->sc->cam.id, rt->sc->cam.ori.x, rt->sc->cam.ori.y, rt->sc->cam.ori.z);
		printf("MAIN: %s FOV: %f\n", rt->sc->cam.id, rt->sc->cam.fov);

		printf("number of objects: %d\n", number_objects(rt->sc->obj));


		free_structures(rt);
	}
	else
	{
		ft_putstr_fd("\033[31m2 args needed :\n\033[0m", 2);
		ft_putstr_fd("\033[31m./miniRT [scene_path]\n\033[0m", 2);
	}
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
