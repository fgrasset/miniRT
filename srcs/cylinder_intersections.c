#include "../incs/minirt.h"

/* function to calculate the intersection between a ray and a cylinder
	it returns the closest distance to the intersection */
t_inter	*intersect_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	t_inter	*inter;
	t_v3d	tr_origin;
	t_v3d	tr_point;
	double	t;
	double	mag;

	inter = malloc(sizeof(t_inter));
	tr_origin = sub(ray->coord, cylinder->coord);
	t = quad((ray->v_dir.x * ray->v_dir.x) + (ray->v_dir.z * ray->v_dir.z), (2 * tr_origin.x * ray->v_dir.x) + (2 * tr_origin.z * ray->v_dir.z), pow(tr_origin.x, 2) + pow(tr_origin.z, 2) - pow(cylinder->r, 2));
	if (t < 0)
	{
		inter->dist = INFINITY;
		return (inter);
	}
	inter->point = add(ray->coord, sc_mult(ray->v_dir, t));
	tr_point = sub(inter->point, cylinder->coord);
	inter->normal = new_v3d(tr_point.x, 0, tr_point.z);
	mag = sqrt(dot_product(inter->normal, inter->normal));
	inter->normal.x /= mag;
	inter->normal.z /= mag;
	inter->dist = t;
	return (inter);
}
