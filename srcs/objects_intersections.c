#include "../incs/minirt.h"

t_inter	*intersect_plane(t_ray *ray, t_plane *plane)
{
	t_inter	*inter;
	double	t;

	inter = malloc(sizeof(t_inter));
	double denominator;
	plane->ori = normalize(plane->ori);
	denominator = dot_product(ray->v_dir, plane->ori);
	if (fabs(denominator) < 1e-6)
	{
		inter->dist = INFINITY;
		return (inter);
	}
	t = dot_product(sub(plane->coord, ray->coord), plane->ori) / denominator;
	// if t is negative, then the plane is behind the ray origin
	if (t < 0)
	{
		inter->dist = INFINITY;
		return (inter);
	}
	inter->type = PLANE;
	inter->dist = t;
	inter->point = add(ray->coord, sc_mult(ray->v_dir, t));
	inter->normal = plane->ori;
	return (inter);
}

// t_inter	intersect_sphere()
// {

// }

// t_inter	intersect_cylinder()
// {

// }
