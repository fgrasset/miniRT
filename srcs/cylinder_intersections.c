#include "../incs/minirt.h"

bool is_intersection_valid(t_ray *ray, t_cylinder *cylinder, double t, double height);

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
// 	double a = (ray->v_dir.x * ray->v_dir.x) + (ray->v_dir.z * ray->v_dir.z);
// 	double b = 2 * ((ray->v_dir.x * tr_origin.x) + (ray->v_dir.z * tr_origin.z));
// 	double c = (tr_origin.x * tr_origin.x) + (tr_origin.z * tr_origin.z) - (cylinder->r * cylinder->r);
// 	// printf("a: %f, b: %f, c: %f\n", a, b, c);
// 	// printf("tr_origin: (%f, %f, %f)\n", tr_origin.x, tr_origin.y, tr_origin.z);
// 	// printf("ray->coord: (%f, %f, %f), ray->v_dir: (%f, %f, %f)\n", ray->coord.x, ray->coord.y, ray->coord.z, ray->v_dir.x, ray->v_dir.y, ray->v_dir.z);
// 	// printf("cylinder->coord: (%f, %f, %f), cylinder->r: %f\n", cylinder->coord.x, cylinder->coord.y, cylinder->coord.z, cylinder->r);

// 	t = quad(a, b, c);
// 	// printf("t = %f\n", t);
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

t_v3d sc_div(t_v3d vec, double scalar) {
	if (scalar != 0) {
		vec.x /= scalar;
		vec.y /= scalar;
		vec.z /= scalar;
	} else {
		// Handle division by zero if necessary
		// You could print an error message, return a specific value, etc.
		printf("Warning: Division by zero in sc_div!\n");
	}
	return vec;
	}

	t_inter *intersect_cylinder(t_ray *ray, t_cylinder *cylinder)
	{
	t_inter *inter;
	double height = cylinder->h; // assuming height is a property of the cylinder

	inter = malloc(sizeof(t_inter));
	inter->type = CYLINDER;
	inter->obj.cy = *cylinder;
	t_v3d X = { ray->coord.x - cylinder->coord.x,
				ray->coord.y - cylinder->coord.y,
				ray->coord.z - cylinder->coord.z };

	// Calculate coefficients of quadratic equation
	double a = dot_product(ray->v_dir, ray->v_dir) - pow(dot_product(ray->v_dir, cylinder->norm_vec), 2);
	double b = 2 * (dot_product(ray->v_dir, X) - (dot_product(ray->v_dir, cylinder->norm_vec) * dot_product(X, cylinder->norm_vec)));
	double c = dot_product(X, X) - pow(dot_product(X, cylinder->norm_vec), 2) - pow(cylinder->r, 2);

	// Solve quadratic equation
	double delta = b * b - 4 * a * c;
	if (delta < 0)
	{
		inter->dist = INFINITY;
		return (inter);
	}

	double t0 = (-b - sqrt(delta)) / (2 * a);
	double t1 = (-b + sqrt(delta)) / (2 * a);

	// Check for intersection within finite bounds
	if (!is_intersection_valid(ray, cylinder, t0, height))
		t0 = t1;
	if (!is_intersection_valid(ray, cylinder, t0, height))
	{
		inter->dist = INFINITY;
		return (inter);
	}

	if (t1 >= 0 && t1 < t0 && is_intersection_valid(ray, cylinder, t1, height))
	{
		inter->dist = t1;
	}
	else
	{
		inter->dist = t0;
	}

	return (inter);
}

bool is_intersection_valid(t_ray *ray, t_cylinder *cylinder, double t, double height)
{
    // Compute intersection point
    t_v3d P_intersection = add(ray->coord, sc_mult(ray->v_dir, t));

    // Compute vector from cylinder base to intersection point
    t_v3d D = sub(P_intersection, cylinder->coord);

    // Project that vector onto cylinder's normal
    double m = dot_product(D, cylinder->norm_vec);

    // Check if m is within the bounds of the cylinder
    return (m >= 0 && m <= height);
}
