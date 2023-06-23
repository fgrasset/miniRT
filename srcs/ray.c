
# include "../incs/minirt.h"

// /* gets the size of the screen and adds it to the rt struct */
// void	make_ray(t_rt *rt)
// {
// 	double	fov_radian;
// 	t_v3d	*forward;
// 	t_v3d	*right;
// 	t_v3d	*up;

// 	// fov_radian = rt->camera->fov * M_PI / 180.0;
// 	// rt->win_h = 2.0 *tan(fov_radian / 2.0);
// 	// rt->win_w = rt->win_h /(WIN_W / WIN_H);
// 	// forward = normalize(rt->camera->dir);
// 	// right = cross(up_vector, forward)	//pas sur que c'est ce qu'il faut faire, mais a tester, need to define up_vector
// 	up = cross(forward, right);
// 	launch_ray(rt, forward, right, up);
// }

// /* launches the ray, gets the color of every pixel and draws it */
// void	launch_ray(t_rt *rt, t_v3d *forward, t_v3d *right, t_v3d *up)
// {
// 	int		x;
// 	int		y;
// 	t_v3d	ray_dir;
// 	double	norm_x;
// 	double	norm_y;

// 	y = -1;
// 	while (++y < WIN_H)
// 	{
// 		x = -1;
// 		while (++x < WIN_W)
// 		{
// 			norm_x = (2.0 * (x + 0.5) / WIN_W - 1.0) * rt->win_w / 2.0;
// 			norm_y = (1.0 - 2.0 * (y + 0.5) / WIN_H) * rt->win_h / 2.0;
// 			ray_dir = normalize(forward + norm_x * right + norm_y * up);
// 			/* now create a function like get_color to launch the ray and get the color of the pixel based on what it intercepts during its travel
// 			then pixel_put with the correct color and that should be a good start */
// 		}
// 	}
// }

// /* normalizes the given vector */
// t_v3d	normalize(t_v3d	*a)
// {
// 	t_v3d	*res;
// 	double	norm;

// 	norm = norme(a);
// 	res->x = a->x / norm;
// 	res->y = a->y / norm;
// 	res->z = a->z / norm;

// 	return (res);
// }


void	make_ray(t_rt *rt)
{
	int	d;
	int	r_h;
	int	r_v;

	(void) r_v;
	d = 2 * tan(rt->sc->camera.fov / 2);
	r_h = 2 * tan(rt->sc->camera.fov / 2) / WIN_W;

}
