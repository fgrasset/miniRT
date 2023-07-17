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
	t_objects	*current;
	(void) ray;

	closest = malloc(sizeof(t_inter));
	// closest->obj = NULL;
	closest->dist = INFINITY;
	current = rt->sc->obj;
	while (current->next)
	{
		// if (current->fig == current->fig.sp)
		// closest = current->fig.	//Issue knowing which kind of object it is, when using fig I have to specify sp, pl, etc.. without knowing which one it is
		// Idea is to use intersect function from each object and get the closer one to return it once we have checked every object
		current = current->next;
	}
	return (closest);
}
