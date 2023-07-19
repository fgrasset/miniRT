#include "../../incs/minirt.h"

void	print_v3d(t_v3d vect)
{
	printf("vect x: %f\n", vect.x);
	printf("vect y: %f\n", vect.y);
	printf("vect z: %f\n", vect.z);
}

void	print_inter(t_inter *inter)
{
	printf("Type: %u\n", inter->type);
	printf("distance: %f\n", inter->dist);
	printf("point vector: \n");
	print_v3d(inter->point);
	printf("normal vector: \n");
	print_v3d(inter->normal);
}
