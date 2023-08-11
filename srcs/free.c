#include "../incs/minirt.h"

void	free_objects(t_rt *rt)
{
	t_objects	*obj;

	while (rt->sc->obj)
	{
		obj = rt->sc->obj->next;
		// if (obj->fig)
		// 	free((void *)obj->fig);
		// {
		// 	if (obj->fig == PLANE)
		// 		free(obj->fig.pl);
		// 	else if (obj->fig == SPHERE)
		// 		free(obj->fig.sp);
		// 	else if (obj->fig == CYLINDER)
		// 		free(obj->fig.cy);
		// }
		free(rt->sc->obj);
		rt->sc->obj = obj;
	}
}

void	free_structures(t_rt *rt)
{
	free_objects(rt);
	free (rt->sc);
	free (rt);
}

/* checks if the intersections exists, then frees it */
void	free_inter(t_inter *inter)
{
	if (inter)
	{
		free (inter);
		inter = NULL;
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free (tab[i]);
			i++;
		}
		free (tab);
	}
}

void	free_scene(t_scene *scene)
{
	if (scene->obj)
		free (scene->obj);
	free (scene);
}

void	free_rt(t_rt *rt)
{
	if (rt->mlbx)
	{
		free (rt->mlbx->img.addr);
		free (rt->mlbx->img.img);
		free (rt->mlbx);
	}
	if (rt->sc)
		free_scene(rt->sc);
	free (rt);
}
