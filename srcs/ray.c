
# include "../incs/minirt.h"

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
			ray.inter = closest_inter(rt, &ray);
			// print_inter(ray.inter);
			//get_color(rt, ray);		TODO
			my_mlx_pixel_put(rt->mlbx->img, x, y, rgb_to_int(ray.inter->c));	//make a function to transfer from rgb to an int for the pixel put function
		}
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

// /* creates the v_dir based on the cam's infos */
// t_v3d	make_v_dir(t_rt *rt, double x, double y)
// {
// 	t_v3d	v_dir;
// 	t_v3d	screen_pos;
// 	t_v3d	s_center;
// 	// double	screen_x;
// 	// double	screen_y;
// 	double	v_fov;
// 	double	h_fov;
// 	double	screen_distance;

// 	//----------------Testing stuff--------------------------

// 	// 	// Assuming that camera is a pointer to your s_camera struct:
// 	// t_v3d forward = rt->sc->cam.ori;

// 	// // Normalize the forward vector, if it isn't already:
// 	// forward = normalize(forward);

// 	// // Choose a general up direction for your world:
// 	// t_v3d world_up = {0, 1, 0};  // or whatever direction is "up" in your scene

// 	// // Calculate the right vector:
// 	// t_v3d right = cross(forward, world_up);

// 	// // Calculate the camera's up vector:
// 	// t_v3d camera_up = cross(right, forward);

// 	// // Normalize the right and up vectors:
// 	// right = normalize(right);
// 	// camera_up = normalize(camera_up);
// 	// double px = (x / (double)WIN_W) * 2 - 1;
// 	// double py = (y / (double)WIN_H) * 2 - 1;

// 	//------------------------------------------


// 	v_fov = rt->sc->cam.fov * M_PI / 180.0;
// 	h_fov = 2 * atan(tan(v_fov / 2) * (WIN_W / WIN_H));

// 	//calculate the distance to screen
// 	screen_distance = (WIN_H / 2) / tan(v_fov / 2);

// 	//calculate the screen center
// 	s_center.x = rt->sc->cam.coord.x + rt->sc->cam.ori.x * screen_distance;
// 	s_center.y = rt->sc->cam.coord.y + rt->sc->cam.ori.y * screen_distance;
// 	s_center.z = rt->sc->cam.coord.z + rt->sc->cam.ori.z * screen_distance;

// 	//scale the pixel to the screen dimensions
// 	screen_pos.x = s_center.x + x * tan(h_fov / 2);
// 	screen_pos.y = s_center.y + y * tan(v_fov / 2) / ((double)WIN_W / (double)WIN_H);
// 	screen_pos.z = s_center.z;

// 	// // scale the pixel to the screen dimensions
// 	// screen_pos.x = s_center.x + right.x * px * tan(h_fov / 2) + camera_up.x * py * tan(v_fov / 2);
// 	// screen_pos.y = s_center.y + right.y * px * tan(h_fov / 2) + camera_up.y * py * tan(v_fov / 2);
// 	// screen_pos.z = s_center.z + right.z * px * tan(h_fov / 2) + camera_up.z * py * tan(v_fov / 2);

// 	v_dir = sub(screen_pos, rt->sc->cam.coord);

// 	return(normalize(v_dir));
// }


t_v3d make_v_dir(t_rt *rt, double x, double y)
{
	// Screen space to world space conversion
	t_v3d	screen_pos;
	t_mat4	view_transform;
	t_v4d	screen_pos_4d;
	t_v4d	v_dir_4d;
	t_v3d	v_dir;

	screen_pos.x = (2.0 * x / WIN_W - 1.0) * tan(rt->sc->cam.fov / 2.0);
	screen_pos.y = (1.0 - 2.0 * y / WIN_H) * tan(rt->sc->cam.fov / 2.0) / ((double)WIN_W / (double)WIN_H);
	screen_pos.z = -1.0; // The screen is located at z=-1

	// World space to camera space conversion
	view_transform = get_view_transform(rt->sc->cam);
	screen_pos_4d = v4d_from_v3d(screen_pos, 1);
	v_dir_4d = mat4_mul_v4d(view_transform, screen_pos_4d);
	v_dir = v4d_to_v3d(v_dir_4d);

	return (normalize(v_dir));
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

