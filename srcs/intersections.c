#include "../incs/minirt.h"

int	is_closest(t_inter *closest, t_inter *temp);

/* retruns the closest intersection in the ray */
t_inter	*closest_inter(t_rt *rt, t_ray *ray)
{
	t_inter		*closest;
	t_inter		*temp;
	t_objects	*curr_fig;

	closest = malloc(sizeof(t_inter));
	closest->dist = INFINITY;
	curr_fig = rt->sc->obj;
	while (curr_fig)
	{
		closest->i = curr_fig->i;
		if (curr_fig->type == PLANE)
			temp = intersect_plane(ray, &curr_fig->fig.pl);
		else if (curr_fig->type == SPHERE)
			temp = intersect_sphere(ray, &curr_fig->fig.sp);
		else if (curr_fig->type == CYLINDER)
			temp = intersect_cylinder(ray, &curr_fig->fig.cy);
		printf("adress: %p\n", temp);
		if (closest && temp->dist > 0 && is_closest(closest, temp))
		{
			if (closest != temp)
				free_inter(closest);
			closest = temp;
		}
		else
		{
			free_inter(temp);
		}
		curr_fig = curr_fig->next;
	}
	return (closest);
}

int	is_closest(t_inter *closest, t_inter *temp)
{
	if (temp->dist == INFINITY && closest->dist)
		return (0);
	if (temp->dist < closest->dist)
		return (1);
	return (0);
}
