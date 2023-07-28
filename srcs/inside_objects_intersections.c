#include "../incs/minirt.h"

int	is_point_in_plane(t_plane *plane, t_v3d *point);
int	is_point_in_sphere(t_sphere *sphere, t_v3d *point);
int	is_point_in_cylinder(t_cylinder *cylinder, t_v3d *point);
float	v3d_len(t_v3d v);

int	is_point_in_object(t_rt *rt, t_v3d *point)
{
	t_objects	*curr_fig;

	curr_fig = rt->sc->obj;
	while (curr_fig)
	{
		if (curr_fig->type == PLANE)
		{
			if (is_point_in_plane(&curr_fig->fig.pl, point))
				return (1);
		}
		else if (curr_fig->type == SPHERE)
		{
			if (is_point_in_sphere(&curr_fig->fig.sp, point))
				return (1);
		}
		else if (curr_fig->type == CYLINDER)
		{
			if (is_point_in_cylinder(&curr_fig->fig.cy, point))
				return (1);
		}
		curr_fig = curr_fig->next;
	}
	return (0);
}

int	is_point_in_plane(t_plane *plane, t_v3d *point)
{
	float	d;

	d = dot_product(plane->ori, *point) - (-dot_product(plane->ori, *point));
	if (d > 0)
		return (1);
	return (0);
}

int	is_point_in_sphere(t_sphere *sphere, t_v3d *point)
{
	float	dist;

	dist = v3d_len(sub(*point, sphere->coord));
	if (dist <= sphere->r)
		return (1);
	return (0);
}

int	is_point_in_cylinder(t_cylinder *cylinder, t_v3d *point)
{
	float	dist, r;

	dist = v3d_len(sub(*point, cylinder->coord));
	r = cylinder->r;
	if (dist > cylinder->h || dist < 0)
		return (0);
	if (fabs(dot_product(*point, cylinder->norm_vec)) > r)
		return (0);
	return (1);
}

float	v3d_len(t_v3d v)
{
	float	len;

	len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return (len);
}
