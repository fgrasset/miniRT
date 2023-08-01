#include "../incs/minirt.h"

t_inter	*intersect_plane(t_ray *ray, t_plane *plane)
{
	t_inter	*inter;
	double	t;
	double	denom;

	inter = ft_calloc(sizeof(t_inter), 1);
	plane->ori = normalize(plane->ori);
	// denom = dot_product(ray->v_dir, plane->ori);
	denom = dot_product(plane->ori, ray->v_dir);
	if (fabs(denom) < 1e-6)
	{
		// printf("the ray is parallel to the plane");
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

// t_inter	*intersect_plane(t_ray *ray, t_plane *plane)
// {
// 	t_inter	*inter;
// 	double	denom;
// 	double	x;

// 	inter = malloc(sizeof(t_inter));
// 	denom = dot_product(plane->ori, ray->v_dir);
// 	if (fabs(denom) > 0)
// 	{
// 		x = dot_product(sub(plane->coord, ray->coord), plane->ori) / denom;
// 		// printf("\t/\t%.2f\t%.2f", x, impact->dist);
// 		if (x > EPSILON && x < inter->dist)
// 		{
// 			// printf("i");
// 			inter->normal = normalize(plane->ori);
// 			inter->point = add(ray->coord, sc_mult(ray->v_dir, x));
// 			inter->point = add(inter->point, sc_mult(inter->normal, EPSILON));
// 			inter->dist = x;
// 			// printf("\t%.2f", impact->dist);
// 			return (inter);
// 		}
// 	}
// 	inter->dist = INFINITY;
// 	return (inter);
// }

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

// bool	solve_quadratic(const t_v3d point, double *x0, double *x1)
// {
// 	double	discr;
// 	double	q;

// 	discr = point.y * point.y - 4 * point.x * point.z;
// 	if (discr < 0)
// 		return (0);
// 	else if (discr == 0)
// 	{
// 		*x0 = -0.5 * point.y / point.x;
// 		*x1 = -0.5 * point.y / point.x;
// 	}
// 	else
// 	{
// 		q = (point.y > 0) ? -0.5 * (point.y + sqrt(discr)) : -0.5 * (point.y - sqrt(discr));
// 		*x0 = q / point.x;
// 		*x1 = point.z / q;
// 	}
// 	if (*x0 > *x1)
// 	{
// 		double tmp = *x0;
// 		x0 = x1;
// 		x1 = &tmp;
// 	}
// 	return (1);
// }

// t_inter	*intersect_sphere(t_ray *ray, t_sphere *sphere)
// {
// 	double	x0;
// 	double	x1;
// 	t_v3d	vect;
// 	t_inter	*inter;

// 	inter = malloc(sizeof(t_inter));
// 	vect = new_v3d(ray->coord.x - sphere->coord.x, ray->coord.y - sphere->coord.y, ray->coord.z - sphere->coord.z);
// 	// printf("ray->v_dir: %f, %f, %f\n", ray->v_dir.x, ray->v_dir.y, ray->v_dir.z);
// 	if (!solve_quadratic(new_v3d(dot_product(ray->v_dir, ray->v_dir), 2 * dot_product(ray->v_dir, vect), dot_product(vect, vect) - sphere->r), &x0, &x1))
// 	{
// 		inter->dist	= INFINITY;
// 		return (inter);
// 	}

// 	if ((x0 < 0 && x1 < 0) || (x0 > inter->dist && x1 > inter->dist))
// 	{
// 		inter->dist = INFINITY;
// 		return (inter);
// 	}
// 	else if (x0 <= 0.)
// 		x0 = x1;
// 	else if (x1 <= 0.)
// 		x1 = x0;
// 	if (x0 < x1)
// 		inter->dist = x0;
// 	else
// 		inter->dist = x1;
// 	inter->point = add(ray->coord, sc_mult(ray->v_dir, x1));
// 	inter->normal = normalize(sub(inter->point, sphere->coord));
// 	inter->point = add(inter->point, sc_mult(inter->normal, EPSILON));
// 	return (inter);
// }

// t_inter	*intersect_sphere(t_ray *ray, t_sphere *sphere)
// {
// 	double	t;
// 	t_inter	*inter;
// 	t_v3d	vec;

// 	inter = malloc(sizeof(t_inter));
// 	vec = new_v3d(ray->coord.x - sphere->coord.x, ray->coord.y - sphere->coord.y, ray->coord.z - sphere->coord.z);
// 	t = quad(dot_product(ray->v_dir, ray->v_dir), 2 * dot_product(ray->v_dir, vec), dot_product(vec	, vec) - sphere->r);
// 	if (t < 0)
// 	{
// 		inter->dist	= INFINITY;
// 		return (inter);
// 	}
// 	inter->dist = t;
// 	inter->point = add(ray->coord, sc_mult(ray->v_dir, t));
// 	inter->normal = normalize(sub(inter->point, sphere->coord));
// 	inter->point = add(inter->point, sc_mult(inter->normal, EPSILON));
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

// t_v3d	convert_cylinder_space(t_v3d *point, t_cylinder *cylinder)
// {
// 	t_v3d	cylinder_space;
// 	t_v3d	aligned_point;
// 	double	dot_product;

// 	cylinder_space.x = point->x - cylinder->coord.x;
// 	cylinder_space.y = point->y - cylinder->coord.y;
// 	cylinder_space.z = point->z - cylinder->coord.z;
// 	dot_product	= cylinder_space.x * cylinder->norm_vec.x + \
// 		cylinder_space.y * cylinder->norm_vec.y + \
// 		cylinder_space.z * cylinder->norm_vec.z;
// 	aligned_point.x = cylinder_space.x - dot_product * cylinder->norm_vec.x;
// 	aligned_point.y = cylinder_space.y - dot_product * cylinder->norm_vec.y;
// 	aligned_point.z = cylinder_space.z - dot_product * cylinder->norm_vec.z;
// 	return (aligned_point);
// }

// t_inter	*intersect_cylinder(t_ray *ray, t_cylinder *cylinder)
// {
// 	t_inter	*inter;
// 	t_v3d	d;
// 	t_v3d	e;
// 	t_v3d	m;
// 	double	t;

// 	inter = ft_calloc(sizeof(t_inter), 1);
// 	d = sub(ray->v_dir, sc_mult(cylinder->norm_vec, \
// 	dot_product(ray->v_dir, cylinder->norm_vec)));
// 	e = sub(sub(ray->coord, cylinder->coord), sc_mult(cylinder->norm_vec, \
// 	dot_product(sub(ray->coord, cylinder->coord), cylinder->norm_vec)));
// 	t = quad(dot_product(d, d), 2.0 * dot_product(d, e), \
// 	dot_product(e, e) - pow(cylinder->r, 2));
// 	if (t < 0)
// 	{
// 		inter->dist = INFINITY;
// 		return (inter);
// 	}
// 	inter->obj.cy = *cylinder;
// 	inter->dist = t;
// 	inter->point = add(ray->coord, sc_mult(ray->v_dir, t));
// 	m = sub(inter->point, cylinder->coord);
// 	inter->normal = normalize(sub(m, \
// 	sc_mult(cylinder->norm_vec,	dot_product(cylinder->norm_vec, m))));
// 	return (inter);
// }
