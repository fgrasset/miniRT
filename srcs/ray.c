
# include "../incs/minirt.h"

t_v3d	normalize(t_v3d	a);
t_v3d	make_v_dir(t_rt *rt, double i, double j);
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
t_v3d	normalize(t_v3d	a)
{
	t_v3d	res;
	double	norm;

	norm = norme(a);
	res.x = a.x / norm;
	res.y = a.y / norm;
	res.z = a.z / norm;

	return (res);
}

/* creates all of the rays */
void	launch_rays(t_rt *rt)
{
	double	x;
	double	y;
	t_ray	ray;

	x = -1;
	while (++x < WIN_W)
	{
		y = -1;
		while (++y < WIN_H)
		{
			ray = make_ray(rt, make_v_dir(rt, x, y));
			// intersection(rt, ray);
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
t_v3d	make_v_dir(t_rt *rt, double x, double y)
{
	t_v3d	v_dir;
	t_v3d	screen_pos;
	// double	a;
	// double	b;
	// double	c;
	// int		max;

	// v_dir = NULL;
	// a = y + 0.5 - WIN_W * 0.5;
	// b = x + 0.5 - WIN_H * 0.5;
	// if (WIN_W > WIN_H)
	// 	max = WIN_W;
	// else
	// 	max = WIN_H;
	// c = max / (2 * tan((rt->sc->cam.fov * M_PI * 0.5) / 180.0));
	// v_dir->x = 1 * a + 0 * b + 0 * c;
	// v_dir->y = 0 * a + 1 * b + 0 * c;
	// v_dir->z = 0 * a + 0 * b + 1 * c;

	double	screen_x;
	double	screen_y;
	double	v_fov;
	double	h_fov;
	double	screen_distance;
	t_v3d	s_center;

	screen_x = (x / (double)WIN_W) * 2 -1;
	screen_y = (y / (double)WIN_H) * 2 -1;
	v_fov = rt->sc->cam.fov * M_PI / 180.0;
	h_fov = 2 * atan(tan(v_fov / 2) * (WIN_W / WIN_H));

	//calculate the distance to screen
	screen_distance = (WIN_H / 2) / tan(v_fov / 2);

	//calculate the screen center
	s_center.x = rt->sc->cam.coord.x + rt->sc->cam.ori.x * screen_distance;
	s_center.y = rt->sc->cam.coord.y + rt->sc->cam.ori.y * screen_distance;
	s_center.z = rt->sc->cam.coord.z + rt->sc->cam.ori.z * screen_distance;

	//scale the pixel to the screen dimensions
	screen_pos.x = s_center.x + x * tan(h_fov / 2);
	screen_pos.y = s_center.y + y * tan(v_fov / 2) / ((double)WIN_W / (double)WIN_H);
	screen_pos.z = s_center.z;

	v_dir = sub(screen_pos, rt->sc->cam.coord);

	return(normalize(v_dir));
}

// t_color calculate_color(t_ray ray, t_intersection intersection) {
//     t_color color = {0, 0, 0};

//     // Calculate the ambient color
//     color = color_add(color, color_multiply(intersection.object->material->ambient_color, ambient_light_color));

//     for each light in the scene {
//         // Calculate the diffuse color
//         t_color diffuse_color = color_multiply(intersection.object->material->diffuse_color, light->color);
//         double diffuse_factor = dot_product(light->direction, intersection.normal);
//         color = color_add(color, color_multiply_scalar(diffuse_color, diffuse_factor));

//         // Calculate the specular color
//         t_color specular_color = color_multiply(intersection.object->material->specular_color, light->color);
//         t_vec3 reflected_light = reflect_vector_around_normal(light->direction, intersection.normal);
//         double specular_factor = pow(max(0, dot_product(ray.direction, reflected_light)), intersection.object->material->shininess);
//         color = color_add(color, color_multiply_scalar(specular_color, specular_factor));
//     }

//     return color;
// }

