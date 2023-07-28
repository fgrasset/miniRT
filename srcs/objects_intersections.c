#include "../incs/minirt.h"

t_inter	*intersect_plane(t_ray *ray, t_plane *plane)
{
	t_inter	*inter;
	double	t;
	double	denom;

	inter = ft_calloc(sizeof(t_inter), 1);
	plane->ori = normalize(plane->ori);
	denom = dot_product(ray->v_dir, plane->ori);
	if (fabs(denom) < 1e-6)
	{
		printf("the ray is parallel to the plane");
		inter->dist = INFINITY;
		return (inter);
	}
	t = dot_product(sub(plane->coord, ray->coord), plane->ori) / denom;
	if (t < 0)
	{
		inter->dist = INFINITY;
		return (inter);
	}
	inter->type = PLANE;
	inter->obj.pl = *plane;
	inter->dist = t;
	inter->point = add(ray->coord, sc_mult(ray->v_dir, t));
	inter->normal = plane->ori;
	return (inter);
}

// t_inter	*intersect_plane(t_ray *ray, t_plane *plane)
// {
// 	t_inter	*inter;
// 	double	denom;
// 	double	t;

// 	inter = ft_calloc(sizeof(t_inter), 1);
// 	denom = dot_product(plane->ori, ray->v_dir);
// 	if (fabs(denom) > 0)
// 	{
// 		t = dot_product(sub(plane->coord, ray->coord), plane->ori) / denom;
// 		if (t > EPSILON)
// 		{
// 			inter->dist = t;
// 			inter->normal = normalize(plane->ori);
// 			inter->point = add(ray->coord, sc_mult(ray->v_dir, t));
// 			inter->point = add(inter->point, sc_mult(inter->normal, EPSILON));
// 		}
// 		else
// 		{
// 			inter->dist = INFINITY;
// 			return (inter);
// 		}
// 	}
// 	else
// 	{
// 		inter->dist = INFINITY;
// 		return (inter);
// 	}
// 	return (inter);
// }


t_inter	*intersect_sphere(t_ray *ray, t_sphere *sphere)
{
	t_inter	*inter;
	t_v3d	oc;
	double	t;

	inter = ft_calloc(sizeof(t_inter), 1);
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

t_v3d	convert_cylinder_space(t_v3d *point, t_cylinder *cylinder)
{
	t_v3d	cylinder_space;
	t_v3d	aligned_point;
	double	dot_product;

	cylinder_space.x = point->x - cylinder->coord.x;
	cylinder_space.y = point->y - cylinder->coord.y;
	cylinder_space.z = point->z - cylinder->coord.z;
	dot_product	= cylinder_space.x * cylinder->norm_vec.x + \
		cylinder_space.y * cylinder->norm_vec.y + \
		cylinder_space.z * cylinder->norm_vec.z;
	aligned_point.x = cylinder_space.x - dot_product * cylinder->norm_vec.x;
	aligned_point.y = cylinder_space.y - dot_product * cylinder->norm_vec.y;
	aligned_point.z = cylinder_space.z - dot_product * cylinder->norm_vec.z;
	return (aligned_point);
}

t_inter	*intersect_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	t_inter	*inter;
	t_v3d	d;
	t_v3d	e;
	t_v3d	m;
	double	t;

	inter = ft_calloc(sizeof(t_inter), 1);
	d = sub(ray->v_dir, sc_mult(cylinder->norm_vec, \
	dot_product(ray->v_dir, cylinder->norm_vec)));
	e = sub(sub(ray->coord, cylinder->coord), sc_mult(cylinder->norm_vec, \
	dot_product(sub(ray->coord, cylinder->coord), cylinder->norm_vec)));
	t = quad(dot_product(d, d), 2.0 * dot_product(d, e), \
	dot_product(e, e) - pow(cylinder->r, 2));
	if (t < 0)
	{
		inter->dist = INFINITY;
		return (inter);
	}
	inter->obj.cy = *cylinder;
	inter->dist = t;
	inter->point = add(ray->coord, sc_mult(ray->v_dir, t));
	m = sub(inter->point, cylinder->coord);
	inter->normal = normalize(sub(m, \
	sc_mult(cylinder->norm_vec,	dot_product(cylinder->norm_vec, m))));
	return (inter);
}
