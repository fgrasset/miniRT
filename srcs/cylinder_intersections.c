#include "../incs/minirt.h"

/* function to calculate the intersection between a ray and a cylinder
	it returns the closest dist to the intersection */
// t_inter	*intersect_cylinder(t_ray *ray, t_cylinder *cylinder)
// {
// 	t_inter	*inter;
// 	t_v3d	tr_origin;
// 	t_v3d	tr_point;
// 	double	t;
// 	double	mag;

// 	inter = malloc(sizeof(t_inter));
// 	tr_origin = sub(ray->coord, cylinder->coord);
// 	t = quad((ray->v_dir.x * ray->v_dir.x) + (ray->v_dir.z * ray->v_dir.z), (2 * tr_origin.x * ray->v_dir.x) + (2 * tr_origin.z * ray->v_dir.z), pow(tr_origin.x, 2) + pow(tr_origin.z, 2) - pow(cylinder->r, 2));
// 	if (t < 0)
// 	{
// 		inter->dist = INFINITY;
// 		return (inter);
// 	}
// 	inter->point = add(ray->coord, sc_mult(ray->v_dir, t));
// 	tr_point = sub(inter->point, cylinder->coord);
// 	inter->normal = new_v3d(tr_point.x, 0, tr_point.z);
// 	mag = sqrt(dot_product(inter->normal, inter->normal));
// 	inter->normal.x /= mag;
// 	inter->normal.z /= mag;
// 	inter->dist = t;
// 	return (inter);
// }

double	solve_plane(t_v3d o, t_v3d d, t_v3d plane_p, t_v3d plane_nv)
{
	double	x;
	double	denom;

	denom = dot_product(plane_nv, d);
	if (denom == 0)
		return (INFINITY);
	x = (dot_product(plane_nv, sub(plane_p, o))) / denom;
	return (x > EPSILON ? x : INFINITY);
}

static double	caps_intersection(t_ray *ray, t_cylinder *cylinder)
{
	double	id1;
	double	id2;
	t_v3d	ip1;
	t_v3d	ip2;
	t_v3d	c2;

	c2 = add(cylinder->coord, sc_mult(cylinder->norm_vec, cylinder->h));
	id1 = solve_plane(ray->coord, ray->v_dir, cylinder->coord, cylinder->norm_vec);
	id2 = solve_plane(ray->coord, ray->v_dir, c2, cylinder->norm_vec);
	if (id1 < INFINITY || id2 < INFINITY)
	{
		ip1 = add(ray->coord, sc_mult(ray->v_dir, id1));
		ip2 = add(ray->coord, sc_mult(ray->v_dir, id2));
		if ((id1 < INFINITY && dist(ip1, cylinder->coord) <= cylinder->r) && (id2 < INFINITY && dist(ip2, c2) <= cylinder->r))
			return (id1 < id2 ? id1 : id2);
		else if (id1 < INFINITY && dist(ip1, cylinder->coord) <= cylinder->r)
			return (id1);
		else if (id2 < INFINITY && dist(ip2, c2) <= cylinder->r)
			return (id2);
	}
	return (INFINITY);
}

static bool	solve_cylinder(double x[2], t_ray *ray, t_cylinder *cylinder)
{
	t_v3d	v;
	t_v3d	u;
	double	a;
	double	b;
	double	c;

	v = sc_mult(cylinder->norm_vec, dot_product(ray->v_dir, cylinder->norm_vec));
	v = sub(ray->v_dir, v);
	u = sc_mult(cylinder->norm_vec, dot_product(sub(ray->coord, cylinder->coord), cylinder->norm_vec));
	u = sub(sub(ray->coord, cylinder->coord), u);
	a = dot_product(v, v);
	b = 2 * dot_product(v, u);
	c = dot_product(u, u) - pow(cylinder->r, 2);
	x[0] = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	x[1] = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	if (x[0] < EPSILON && x[1] < EPSILON)
		return (0);
	return (1);
}

static void		calc_cy_normal(double x2[2], t_cylinder *cylinder, double dist1, double dist2)
{
	double	dist;
	double	x;

	if ((dist1 >= 0 && dist1 <= cylinder->h && x2[0] > EPSILON) && (dist2 >= 0 && dist2 <= cylinder->h && x2[1] > EPSILON))
	{
		dist = x2[0] < x2[1] ? dist1 : dist2;
		x = x2[0] < x2[1] ? x2[0] : x2[1];
	}
	else if (dist1 >= 0 && dist1 <= cylinder->h && x2[0] > EPSILON)
	{
		dist = dist1;
		x = x2[0];
	}
	else
	{
		dist = dist2;
		x = x2[1];
	}
	x2[0] = x;
	// return (normalize(sub(sub(sc_mult(ray->v_dir, x),	sc_mult(cylinder.norm_vec, dist)), sub(cylinder.coord, ray.coord))));
}

static double	cy_intersection(t_ray *ray, t_cylinder *cylinder)
{
	double	x2[2];

	if (!solve_cylinder(x2, ray, cylinder))
		return (INFINITY);
	double dist1 = dot_product(cylinder->norm_vec, sub(sc_mult(ray->v_dir, x2[0]), sub(cylinder->coord, ray->coord)));
	double dist2 = dot_product(cylinder->norm_vec, sub(sc_mult(ray->v_dir, x2[1]), sub(cylinder->coord, ray->coord)));
	if (!((dist1 >= 0 && dist1 <= cylinder->h && x2[0] > EPSILON) || (dist2 >= 0 && dist2 <= cylinder->h && x2[0] > EPSILON)))
		return (INFINITY);
	calc_cy_normal(x2, cylinder, dist1, dist2);
	return (x2[0]);
}

double	cylinder_intersection(t_ray *ray, t_cylinder *cylinder, bool *is_on_side)
{
	double	cylinder_inter;
	double	caps_inter;

	cylinder_inter = cy_intersection(ray, cylinder);
	caps_inter = caps_intersection(ray, cylinder);
	if (cylinder_inter < INFINITY || caps_inter < INFINITY)
	{
		if (cylinder_inter < caps_inter)
		{
			*is_on_side = true;
			return (cylinder_inter);
		}
		return (caps_inter);
	}
	return (INFINITY);
}

t_v3d get_closest_point_from_line(t_v3d A, t_v3d B, t_v3d P)
{
	t_v3d AP = sub(P, A);
	t_v3d AB = sub(B, A);
	double ab2 = dot_product(AB, AB);
	double ap_ab = dot_product(AP, AB);
	double t = ap_ab / ab2;
	if (t < 0.0)
		t = 0.0;
	else if (t > 1.0)
		t = 1.0;
	return (add(A, sc_mult(AB, t)));
}

t_inter	*intersect_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	t_inter		*inter;

	double		t;
	bool		is_on_side;

	inter = malloc(sizeof(t_inter));
	is_on_side = false;
	if ((t = cylinder_intersection(ray, cylinder, &is_on_side)) > 0)
	{
		inter->dist = t;
		inter->point = new_v3d(t * ray->v_dir.x, t * ray->v_dir.y, t * ray->v_dir.z);
		if (is_on_side)
			inter->normal = sub(get_closest_point_from_line(cylinder->coord, add(cylinder->coord, sc_mult(cylinder->norm_vec, cylinder->h)), inter->point), inter->point);
		else
			inter->normal = cylinder->norm_vec;
		inter->normal = normalize(inter->normal);
		return (inter);
	}
	inter->dist = INFINITY;
	return (inter);
}
