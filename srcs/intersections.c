#include "../incs/minirt.h"

/*
calculate the intersection
maybe create a struct intersection that the distance to the ray's origin
and the objects which is closer, it also contains the normal at the intersection
and the intersection coordinates

Then I need one function to iterate through all the objects we have in the scene
*/

/* retruns the closest intersection in the ray */
t_inter	*closest_inter(t_rt *rt, t_ray *ray)
{
	t_inter		*closest;
	t_inter		*temp;
	t_objects	*curr_fig;

	closest = malloc(sizeof(t_inter));
	closest->dist = INFINITY;
	curr_fig = rt->sc->obj;
	while (curr_fig->next)
	{
		if (curr_fig->type == PLANE)
			temp = intersect_plane(ray, &curr_fig->fig.pl);
		else if (curr_fig->type == SPHERE)
			temp = intersect_sphere(ray, &curr_fig->fig.sp);
		else if (curr_fig->type == CYLINDER)
			temp = intersect_cylinder(ray, &curr_fig->fig.cy);

		if (temp->dist > 0 && temp->dist < closest->dist && is_point_in_object(rt, &temp->point))
			closest = temp;
		// closest = curr_fig->fig.
		// Idea is to use intersect function from each object and get the closer one to return it once we have checked every object
		// printf("distance: %f\n", closest->dist);
		// printf("point : \n");
		// print_v3d(closest->point);
		// printf("normal : \n");
		// print_v3d(closest->normal);
		curr_fig = curr_fig->next;
	}
	if (closest->type == PLANE)
		closest->c = closest->obj.pl.color;
	else if (closest->type == SPHERE)
		closest->c = closest->obj.sp.color;
	else if (closest->type == CYLINDER)
		closest->c = closest->obj.cy.color;
	return (closest);
	return (closest);
}

// void	limits(t_rt *rt, int i, int j)
// {
// 	t_v3d	start;
// 	t_v3d	end;

// 	start.x = data->f_map[i][j].x;
// 	start.y = data->f_map[i][j].y;
// 	if (i < data->y_max - 1 && j < data->x_max - 1)
// 	{
// 		assign(data, &end, i, j + 1);
// 		line(data, &start, &end);
// 		assign (data, &end, i + 1, j);
// 		line(data, &start, &end);
// 	}
// 	else if (i < data->y_max - 1 && j == data->x_max - 1)
// 	{
// 		assign (data, &end, i + 1, j);
// 		line(data, &start, &end);
// 	}
// 	else if (i == data->y_max - 1 && j < data->x_max - 1)
// 	{
// 		assign (data, &end, i, j + 1);
// 		line(data, &start, &end);
// 	}
// 	else
// 		return ;
// }
