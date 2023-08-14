#include "../incs/minirt.h"

t_inter	*intersect_plane(t_ray *ray, t_plane *plane)
{
	t_inter	*inter;
	double	t;
	double	denom;

	inter = malloc(sizeof(t_inter));
	plane->ori = normalize(plane->ori);
	denom = dot_product(plane->ori, ray->v_dir);
	if (fabs(denom) < 1e-6)
	{
		inter->dist = INFINITY;
		return (inter);
	}
	t = dot_product(sub(plane->coord, ray->coord), plane->ori) / denom;
	if (t < EPSILON)
	{
		inter->dist = INFINITY;
		return (inter);
	}
	inter->type = PLANE;
	inter->obj.pl = *plane;
	inter->dist = t;
	inter->point = add(ray->coord, sc_mult(ray->v_dir, t));
	inter->point = add(inter->point, sc_mult(inter->normal, EPSILON));
	inter->normal = plane->ori;
	return (inter);
}

t_inter	*intersect_sphere(t_ray *ray, t_sphere *sphere)
{
	t_inter	*inter;
	t_v3d	oc;
	double	t;

	inter = malloc(sizeof(t_inter));
	oc = sub(ray->coord, sphere->coord);
	t = quad(dot_product(ray->v_dir, ray->v_dir), 2.0 * \
	dot_product(oc, ray->v_dir), dot_product(oc, oc) - sphere->r * sphere->r);
	if (t < 0)
	{
		inter->dist = INFINITY;
		return (inter);
	}
	inter->type = SPHERE;
	inter->obj.sp = *sphere;
	inter->dist = t;
	inter->point = add(ray->coord, sc_mult(ray->v_dir, t));
	inter->normal = normalize(sub(inter->point, sphere->coord));
	return (inter);
}
