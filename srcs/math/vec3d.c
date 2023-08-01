#include "../../incs/minirt.h"

/* returns a+b */
t_v3d	add(t_v3d a, t_v3d b)
{
	t_v3d	res;

	res.x = a.x + b.x;
	res.y = a.y + b.y;
	res.z = a.z + b.z;
	return (res);
}

/* returns a-b */
t_v3d	sub(t_v3d a, t_v3d b)
{
	t_v3d	res;

	res.x = a.x - b.x;
	res.y = a.y - b.y;
	res.z = a.z - b.z;
	return (res);
}

t_v3d	new_v3d(double x, double y, double z)
{
	t_v3d	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

/* multiplication by a scalar */
t_v3d	sc_mult(t_v3d a, double nb)
{
	t_v3d	res;

	res.x = a.x * nb;
	res.y = a.y * nb;
	res.z = a.z * nb;
	return (res);
}

/* returns ||a|| */
double	norme(t_v3d a)
{
	double res;

	res = sqrt(pow(a.x, 2.0) + pow(a.y, 2.0) + pow(a.z, 2.0));
	return (res);
}

/* returns axb (cross product) */
t_v3d	cross(t_v3d a, t_v3d b)
{
	t_v3d	res;

	res.x = a.y * b.z - a.z * b.y;
	res.y = a.z * b.x - a.x * b.z;
	res.z = a.x * b.y - a.y * b.x;
	return (res);
}

/* multiplies 2 vectors */
t_v3d	mult(t_v3d a, t_v3d b)
{
	t_v3d	res;

	res.x = a.x * b.x;
	res.y = a.y * b.y;
	res.z = a.z * b.z;
	return (res);
}

double	dot_product_v3d(t_v3d v1, t_v3d v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
