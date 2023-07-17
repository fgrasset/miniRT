#include "../incs/minirt.h"

/*
calculate the intersection
maybe create a struct intersection that the distance to the ray's origin
and the objects which is closer, it also contains the normal at the intersection
and the intersection coordinates

Then I need one function to iterate through all the objects we have in the scene
*/

/* retruns the closest intersection in the ray */
t_inter	*closest_inter(t_rt *rt, t_ray *ray)
{
	t_inter		*closest;
	t_objects	*curr_fig;
	(void) ray;

	closest = malloc(sizeof(t_inter));
	// closest->obj = NULL;
	closest->dist = INFINITY;
	curr_fig = rt->sc->obj;
	while (curr_fig->next)
	{
		if (curr_fig->type == PLANE)
			closest = intersect_plane(ray, &curr_fig->fig.pl);
		// else if (curr_fig->type == SPHERE)
		// 	intersect_sphere();
		// else if (curr_fig->type == CYLINDER)
		// 	intersect_cylinder();
		// closest = curr_fig->fig.
		// Idea is to use intersect function from each object and get the closer one to return it once we have checked every object
		curr_fig = curr_fig->next;
	}
	return (closest);
}
