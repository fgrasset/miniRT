
# include "../incs/minirt.h"

t_v3d	normalize(t_v3d	a);
t_v3d	make_v_dir(t_rt *rt, double i, double j);
t_ray	make_ray(t_rt *rt, t_v3d v_dir);

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
			closest_inter(rt, &ray);
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
	t_v3d	s_center;
	// double	screen_x;
	// double	screen_y;
	double	v_fov;
	double	h_fov;
	double	screen_distance;

	// screen_x = (x / (double)WIN_W) * 2 -1;
	// screen_y = (y / (double)WIN_H) * 2 -1;
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

