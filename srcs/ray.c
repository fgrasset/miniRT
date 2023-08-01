
# include "../incs/minirt.h"

t_v3d	make_v_dir(t_rt *rt, double i, double j);
t_ray	make_ray(t_rt *rt, t_v3d v_dir);

// /* normalizes the given vector */
// t_v3d	normalize(t_v3d	a)
// {
// 	t_v3d	res;
// 	double	norm;

// 	norm = norme(a);
// 	res.x = a.x / norm;
// 	res.y = a.y / norm;
// 	res.z = a.z / norm;

// 	return (res);
// }

double	dist(const t_v3d p1, const t_v3d p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2)));
}

t_v3d	normalize(t_v3d a)
{
	double	length;

	length = dist(new_v3d(0,0,0), a);
	return (new_v3d(a.x / length, a.y / length, a.z / length));
}

/* creates all of the rays */
void	launch_rays(t_rt *rt)
{
	double	x;
	double	y;
	t_ray	ray;
	t_color	final_color;

	y = -1;
	while (++y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
		{
			ray = make_ray(rt, make_v_dir(rt, x, y));
			// printf("ray.coord: %f, %f, %f\n", ray.coord.x, ray.coord.y, ray.coord.z);
			ray.inter = closest_inter(rt, &ray);
			// print_inter(ray.inter);
			final_color = get_color(ray.inter);
			final_color = lights_shadows(rt, rt->sc, ray.inter, final_color);
			my_mlx_pixel_put(rt->mlbx->img, x, y, rgb_to_int(final_color));	//make a function to transfer from rgb to an int for the pixel put function
		}
	}
}

t_ray	make_ray(t_rt *rt, t_v3d dir)
{
	t_ray	ray;
	ray.coord = rt->sc->cam.coord;
	ray.v_dir = dir;
	return (ray);
}

t_v3d	make_v_dir(t_rt *rt, double x, double y)
{
	t_v3d	v_dir;
	double	a;
	double	b;
	double	c;
	int		max;

	a = x + 0.5 - (WIN_W) * 0.5;
	b = y + 0.5 - (WIN_H) * 0.5;
	max = WIN_W > WIN_H ? WIN_W : WIN_H;
	c = max / (2 * tan((rt->sc->cam.fov * 0.5) * M_PI / 180.0));
	v_dir.x = 1 * a + 0 * b + 0 * c;
	v_dir.y = 0 * a + 1 * b + 0 * c;
	v_dir.z = 0 * a + 0 * b + 1 * c;
	return (normalize(v_dir));
}


// /* creates a ray */
// t_ray	make_ray(t_rt *rt, t_v3d v_dir)
// {
// 	t_ray	ray;

// 	ray.coord = rt->sc->cam.coord;
// 	ray.v_dir = v_dir;
// 	return(ray);
// }

// t_v3d make_v_dir(t_rt *rt, double x, double y)
// {
// 	t_v3d	v_dir;
// 	double	scale;
// 	double	ratio;

// 	ratio = WIN_W / (double)WIN_H;
// 	scale = tan((rt->sc->cam.fov * 0.5) * M_PI / 180.0);
// 	x = -(2 * (x + 0.5) / WIN_W - 1) * scale * ratio;
// 	y = -(1 - 2 * (y + 0.5) / WIN_H) * scale;

// 	// Construct the ray direction in camera space
// 	v_dir = new_v3d(x, y, -1);

// 	// Transform the ray direction to world space
// 	v_dir = mat4_mul_v3d(get_inverse_view_transform(rt->sc->cam), v_dir);

// 	// Normalize the ray direction
// 	return (normalize(v_dir));
// }

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

