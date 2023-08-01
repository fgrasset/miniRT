/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbian <lfabbian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:25:43 by lfabbian          #+#    #+#             */
/*   Updated: 2023/07/28 16:05:55 by lfabbian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/minirt.h"

void	print_sphere_details(const t_sphere *sphere)
{
	printf("ID: %s\n", sphere->id);
	printf("Coordinates: (%f, %f, %f)\n", sphere->coord.x,
		sphere->coord.y, sphere->coord.z);
	printf("Radius: %f\n", sphere->r);
	printf("Color: RGB(%d, %d, %d)\n\n", sphere->color.r,
		sphere->color.g, sphere->color.b);
}

void	print_cylinder_details(const t_cylinder *cylinder)
{
	printf("ID: %s\n", cylinder->id);
	printf("Coordinates: (%f, %f, %f)\n", cylinder->coord.x,
		cylinder->coord.y, cylinder->coord.z);
	printf("Normal Vector: (%f, %f, %f)\n", cylinder->norm_vec.x,
		cylinder->norm_vec.y, cylinder->norm_vec.z);
	printf("Radius: %f\n", cylinder->r);
	printf("Height: %f\n", cylinder->h);
	printf("Color: RGB(%d, %d, %d)\n\n", cylinder->color.r,
		cylinder->color.g, cylinder->color.b);
}

void	print_plane_details(const t_plane *plane)
{
	printf("ID: %s\n", plane->id);
	printf("Coordinates: (%f, %f, %f)\n", plane->coord.x,
		plane->coord.y, plane->coord.z);
	printf("Orientation Vector: (%f, %f, %f)\n",
		plane->ori.x, plane->ori.y, plane->ori.z);
	printf("Color: RGB(%d, %d, %d)\n\n", plane->color.r,
		plane->color.g, plane->color.b);
}

void	print_objects(const t_objects *obj)
{
	while (obj != NULL)
	{
		printf("NUMBER OF OBJECT: %d\n", obj->i);
		switch (obj->type)
		{
			case PLANE:
				print_plane_details(&obj->fig.pl);
				break;
			case SPHERE:
				print_sphere_details(&obj->fig.sp);
				break;
			case CYLINDER:
				print_cylinder_details(&obj->fig.cy);
				break;
		}
		obj = obj->next;
	}
}
