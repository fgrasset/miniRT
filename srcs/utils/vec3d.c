
# include "../../incs/minirt.h"

/* performs a+b */
t_v3d	add(t_v3d *a, t_v3d *b)
{
	t_v3d	*res;

	res->x = a->x + b->x;
	res->y = a->y + b->y;
	res->z = a->z + b->z;
	return (res);
}

/* performs a-b */
t_v3d	sub(t_v3d *a, t_v3d *b)
{
	t_v3d	*res;

	res->x = a->x - b->x;
	res->y = a->y - b->y;
	res->z = a->z - b->z;
	return (res);
}

/* multiplication by a scalar */
t_v3d	sc_mult(t_v3d *a, double nb)
{
	t_v3d	*res;

	res->x = a->x * nb;
	res->y = a->y * nb;
	res->z = a->z * nb;
	return (nb);
}

/* performes ||a|| */
double	norme(t_v3d *a)
{
	double res;

	res = sqrt(pow(a->x, 2.0) + pow(a->y, 2.0) + pow(a->z, 2.0));
	return (res);
}

/* performs a*b */
double	mult(t_v3d *a, t_v3d *b)
{
	double	res;

	res = (a->x * b->x) + (a->y * b->y) + (a->z * b->z);
	return (res);
}
