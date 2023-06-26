
# include "../incs/minirt.h"

t_v3d	normalize(t_v3d	*a);
t_v3d	make_v_dir(t_rt *rt, int i, int j);
t_ray	make_ray(t_rt *rt, t_v3d v_dir);
void	launch_rays(t_rt *rt);


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

/* normalizes the given vector */
t_v3d	normalize(t_v3d	*a)
{
	t_v3d	*res;
	double	norm;

	res = NULL;
	norm = norme(a);
	res->x = a->x / norm;
	res->y = a->y / norm;
	res->z = a->z / norm;

	return (*res);
}

/* creates all of the rays */
void	launch_rays(t_rt *rt)
{
	int		x;
	int		y;
	t_ray	ray;

	x = -1;
	while (++x < WIN_W)
	{
		y = -1;
		while (++y < WIN_H)
		{
			ray = make_ray(rt, make_v_dir(rt, x, y));
			//get_color(rt, ray);		TODO
		}
		// my_mlx_pixel_put(rt->mlbx->img, x, y, ray->rgb);	//make a function to transfer from rgb to an int for the pixel put function
	}
}

/* creates a ray */
t_ray	make_ray(t_rt *rt, t_v3d v_dir)
{
	t_ray	ray;

	ray.coord = rt->sc->cam.coord;
	ray.v_dir = v_dir;
	return(ray);
}

/* creates the v_dir based on the cam's infos */
t_v3d	make_v_dir(t_rt *rt, int x, int y)
{
	t_v3d	*v_dir;
	double	a;
	double	b;
	double	c;
	int		max;

	v_dir = NULL;
	a = y + 0.5 - WIN_W * 0.5;
	b = x + 0.5 - WIN_H * 0.5;
	if (WIN_W > WIN_H)
		max = WIN_W;
	else
		max = WIN_H;
	c = max / (2 * tan((rt->sc->cam.fov * M_PI * 0.5) / 180.0));
	v_dir->x = 1 * a + 0 * b + 0 * c;
	v_dir->y = 0 * a + 1 * b + 0 * c;
	v_dir->z = 0 * a + 0 * b + 1 * c;

	return(normalize(v_dir));
}
