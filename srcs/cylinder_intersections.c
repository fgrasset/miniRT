#include "../incs/minirt.h"

bool	is_intersection_valid(t_ray *ray, t_cylinder *cy, double t, double h);
t_v3d	cylinder_normal(t_v3d P, t_cylinder *cylinder);
int		quad_cylinder(t_ray *ray, t_inter *inter, \
t_cylinder *cylinder, t_v3d X);

t_inter	*intersect_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	t_inter	*inter;
	t_v3d	x;

	inter = malloc(sizeof(t_inter));
	inter->type = CYLINDER;
	inter->obj.cy = *cylinder;
	x = new_v3d(ray->coord.x - cylinder->coord.x, ray->coord.y - \
	cylinder->coord.y, ray->coord.z - cylinder->coord.z);
	if (!quad_cylinder(ray, inter, cylinder, x))
		return (inter);
	inter->point = add(ray->coord, sc_mult(ray->v_dir, inter->dist));
	inter->normal = cylinder_normal(inter->point, cylinder);
	return (inter);
}

int	quad_cylinder(t_ray *ray, t_inter *inter, t_cylinder *cylinder, t_v3d X)
{
	double	quad[4];
	double	dist[2];

	quad[0] = dot_product(ray->v_dir, ray->v_dir) \
	- pow(dot_product(ray->v_dir, cylinder->norm_vec), 2);
	quad[1] = 2 * (dot_product(ray->v_dir, X) - \
	(dot_product(ray->v_dir, cylinder->norm_vec) \
	* dot_product(X, cylinder->norm_vec)));
	quad[2] = dot_product(X, X) - \
	pow(dot_product(X, cylinder->norm_vec), 2) - pow(cylinder->r, 2);
	quad[3] = quad[1] * quad[1] - 4 * quad[0] * quad[2];
	if (quad[3] < 0)
		return (inter->dist = INFINITY, 0);
	dist[0] = (-quad[1] - sqrt(quad[3])) / (2 * quad[0]);
	dist[1] = (-quad[1] + sqrt(quad[3])) / (2 * quad[0]);
	if (!is_intersection_valid(ray, cylinder, dist[0], cylinder->h))
		dist[0] = dist[1];
	if (!is_intersection_valid(ray, cylinder, dist[0], cylinder->h))
		return (inter->dist = INFINITY, 0);
	if (dist[1] >= 0 && dist[1] < dist[0] && \
	is_intersection_valid(ray, cylinder, dist[1], cylinder->h))
		inter->dist = dist[1];
	else
		inter->dist = dist[0];
	return (1);
}

bool	is_intersection_valid(t_ray *ray, t_cylinder *cy, double t, double h)
{
	t_v3d	p_intersection;
	t_v3d	d;
	double	m;

	p_intersection = add(ray->coord, sc_mult(ray->v_dir, t));
	// Compute vector from cy base to intersection point
	d = sub(p_intersection, cy->coord);
	// Project that vector onto cy's normal
	m = dot_product(d, cy->norm_vec);
	// Check if m is within the bounds of the cylinder
	return (m >= 0 && m <= h);
}

t_v3d	cylinder_normal(t_v3d P, t_cylinder *cylinder)
{
	t_v3d	cp;
	t_v3d	norm_dir;
	t_v3d	normal;
	double	m;
	double	length;

	cp = sub(P, cylinder->coord);
	// Project that vector onto cylinder's normal
	m = dot_product(cp, cylinder->norm_vec);
	// Subtracting the projection from the intersection point gives a vector
	// that is perpendicular to the cylinder's axis (or normal vector).
	norm_dir = sub(cp, sc_mult(cylinder->norm_vec, m));
	// Normalize this direction to get the normal at the intersection point
	length = sqrt(dot_product(norm_dir, norm_dir));
	normal = new_v3d(norm_dir.x / length, norm_dir.y \
	/ length, norm_dir.z / length);
	return (normal);
}
