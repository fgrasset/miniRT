/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbian <lfabbian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 14:19:12 by lfabbian          #+#    #+#             */
/*   Updated: 2023/07/26 13:16:03 by lfabbian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minirt.h"

double distance(t_v3d *p1, t_v3d *p2) {
    double dx = p2->x - p1->x;
    double dy = p2->y - p1->y;
    double dz = p2->z - p1->z;

    return sqrt(dx * dx + dy * dy + dz * dz);
}

t_v3d subtract_vectors(t_v3d v1, t_v3d v2)
{
    t_v3d result;
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;
    return result;
}

t_color int_to_rgb(const int r, const int g, const int b)
{
	t_color	rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}

t_color get_color(t_inter *inter)
{
    if (inter->type == PLANE)
		inter->c = inter->obj.pl.color;
	else if (inter->type == SPHERE)
		inter->c = inter->obj.sp.color;
	else if (inter->type == CYLINDER)
		inter->c = inter->obj.cy.color;
	return (inter->c);
}

t_color ambiance_color(t_color color, t_ambiant amb)
{
    t_color ambient_color;

    ambient_color.r = color.r * amb.color.r * amb.ratio;
    ambient_color.g = color.g * amb.color.g * amb.ratio;
    ambient_color.b = color.b * amb.color.b * amb.ratio;
    return (ambient_color);
}

double dot_product_v3d(t_v3d v1, t_v3d v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

t_color diffuse_color(t_inter *inter, t_light *light, t_color color)
{
    // t_v3d normal = inter->normal;
    t_v3d light_dir = normalize(subtract_vectors(light->coord, inter->point));
    double dot_product = dot_product_v3d(inter->normal, light_dir);
    double diffuse_factor = fmax(0.0, dot_product) * light->ratio;

    t_color diffuse_color;
    diffuse_color.r = inter->c.r * diffuse_factor;
    diffuse_color.g = inter->c.g * diffuse_factor;
    diffuse_color.b = inter->c.b * diffuse_factor;
    color.r += diffuse_color.r;
    color.g += diffuse_color.g;
    color.b += diffuse_color.b;
    return (color);
}

bool intersect_obj(t_rt *rt, t_ray *ray, double max_distance)
{
    t_objects *objects = rt->sc->obj;
    t_inter *impact_obstacle;

    impact_obstacle = malloc(sizeof(t_inter));
    while (objects)
    {
        impact_obstacle = closest_inter(rt, ray);
        if (impact_obstacle && impact_obstacle->dist < max_distance)
        {
            free (impact_obstacle);
            return (true);
        }
        objects = objects->next;
    }
    free (impact_obstacle);
    return (false);
}

t_color shadow_color(t_color color, double shadow_intensity)
{
    t_color shadow_color;
    shadow_color.r = color.r * shadow_intensity;
    shadow_color.g = color.g * shadow_intensity;
    shadow_color.b = color.b * shadow_intensity;
    return shadow_color;
}


t_color lights_shadows(t_rt *rt, t_scene *sc, t_inter *inter, t_color color)
{
    t_ray   to_light;
    t_color final_color;
    bool    is_in_shadow;

    final_color = ambiance_color(color, sc->amb);
    to_light.coord = inter->point;
    to_light.v_dir = normalize(subtract_vectors(sc->light.coord, inter->point));
    is_in_shadow = intersect_obj(rt, &to_light, distance(&to_light.coord, &sc->light.coord));
    if (!is_in_shadow) //donc si va direct dans la lumiere
        final_color = diffuse_color(inter, &sc->light, final_color);
    else //donc s'il intercepte un objet
        final_color = shadow_color(final_color, 0.5);
    return (final_color);
}
