#include "../incs/minirt.h"

bool	inter_obj(t_rt *rt, t_ray *ray, double max_distance)
{
	t_objects	*objects;
	t_inter		*closest_intersection;
	t_inter		*intersection;
	bool		is_in_shadow;

	objects = rt->sc->obj;
	closest_intersection = NULL;
	is_in_shadow = false;
	while (objects)
	{
		if (objects->i == ray->inter->i)
		{
			objects = objects->next;
			continue ;
		}
		intersection = NULL;
		if (objects->type == PLANE)
			intersection = intersect_plane(ray, &objects->fig.pl);
		else if (objects->type == SPHERE)
			intersection = intersect_sphere(ray, &objects->fig.sp);
		else if (objects->type == CYLINDER)
			intersection = intersect_cylinder(ray, &objects->fig.cy);
		if (intersection && intersection->dist > EPSILON && intersection->dist < max_distance)
		{
			max_distance = intersection->dist;
			if (closest_intersection)
				free(closest_intersection);
			closest_intersection = intersection;
			is_in_shadow = true;
		}
		else
			free(intersection);
		objects = objects->next;
	}
	if (closest_intersection)
	{
		if (ray->inter)
			free(ray->inter);
		ray->inter = closest_intersection;
	}
	return (is_in_shadow);
}

t_color	lights_shadows(t_rt *rt, t_scene *sc, t_inter *inter, t_color color)
{
	t_ray	to_light;
	t_color	final_color;
	bool	shad;

	final_color = ambiance_color(color, sc->amb);
	to_light.coord = inter->point;
	to_light.v_dir = normalize(sub(sc->light.coord, inter->point));
	shad = inter_obj(rt, &to_light, dst(&to_light.coord, &sc->light.coord));
	if (!shad)
		final_color = diffuse_color(inter, &sc->light, final_color);
	if (shad)
		final_color = shadow_color(final_color, 1);
	return (final_color);
}
