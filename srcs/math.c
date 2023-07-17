#include "../incs/minirt.h"

/* calculates a quadratic equation and returns the result with
	the first intersection only in case of 2 intersections
	returns false if no result
	true if 1 or 2 results */
double	quad(double a, double b, double c)
{
	double	delta;
	double	sub;
	double	add;

	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (0);
	add = (-b + sqrt(delta)) / (2 * a);
	sub = (-b - sqrt(delta)) / (2 * a);
	if (sub < add)
		return (sub);
	else
		return (add);
}

/* returns the dot product of 2 vectors */
double dot_product(t_v3d a, t_v3d b)
{
	return (a.x*b.x + a.y*b.y + a.z*b.z);
}

