#ifndef PROTOTYPES_H
# define PROTOTYPES_H
# include "minirt.h"

/* ERROR HANDLING */
int		print_error(char *error_message);

/* PARSING */
void	parsing(char *file);

/* MAKE WINDOW */
void	make_window(t_rt *rt);

/* v3d */
t_v3d	add(t_v3d *a, t_v3d *b);
t_v3d	sub(t_v3d *a, t_v3d *b);
t_v3d	sc_mult(t_v3d *a, double nb);
double	norme(t_v3d *a);
double	mult(t_v3d *a, t_v3d *b);
t_v3d	normalize(t_v3d	*a);

#endif
