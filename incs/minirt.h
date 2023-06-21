#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include "../mlx/mlx.h"
# include "../libft/libft.h"

# include "structures.h"

# define WIN_H 800
# define WIN_W 600

/* main structure used for everything */
typedef struct s_rt
{
	int		win_w;
	int		win_h;
	t_mlbx	*mlbx;
} t_rt;

# include "prototypes.h"

#endif
