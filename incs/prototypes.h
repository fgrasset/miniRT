#ifndef PROTOTYPES_H
# define PROTOTYPES_H
# include "minirt.h"

/* ERROR HANDLING */
int		print_error(char *error_message);

/* PARSING */
void file_parsing(char *file);

/* MAKE WINDOW */
void	make_window(t_rt *rt);

#endif
