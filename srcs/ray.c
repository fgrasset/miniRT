
# include "../incs/minirt.h"

/* gets the size of the screen and adds it to the rt struct */
void	make_ray(t_rt *rt)
{
	double	fov_radian;
	t_v3d	*forward;
	t_v3d	*right;
	t_v3d	*up;

	fov_radian = rt.camera.fov * M_PI / 180.0;
	rt->win_h = 2.0 *tan(fov_radian / 2.0);
	rt->win_w = rt->win_h /(WIN_W / WIN_H);
	// forward = normalize(rt.camera.dir);
	right =
}

void	launch_ray(t_rt *rt, t_v3d *forward, t_v3d *right, t_v3d *up)
{

}

/* normalizes the given vector */
t_v3d	normalize(t_v3d	*a)
{
	t_v3d	*res;
	double	norm;

	norm = norme(a);
	res->x = a->x / norm;
	res->y = a->y / norm;
	res->z = a->z / norm;

	return (res);
}
