# include "../incs/minirt.h"

int		destroy(t_rt *rt);
int		display(t_rt *rt);
void	my_mlx_pixel_put(t_rt *rt, int x, int y, int color);
void	background(t_rt	*rt);


/* creates the graphical window */
void	make_window(t_rt *rt)
{
	t_mlbx	*mlbx;

	mlbx = malloc(sizeof(t_mlbx));
	rt->mlbx = mlbx;
	rt->mlbx->mlx = mlx_init();
	rt->mlbx->mlx_win = mlx_new_window(rt->mlbx->mlx,rt->win_w, rt->win_h, "MiniRT");
	rt->mlbx->img.img = mlx_new_image(rt->mlbx->mlx, rt->win_w, rt->win_h);
	rt->mlbx->img.addr = mlx_get_data_addr(rt->mlbx->img.img, &rt->mlbx->img.bits_per_pixel, &rt->mlbx->img.line_length, &rt->mlbx->img.endian);
	mlx_hook(rt->mlbx->mlx_win, 17, 0, destroy, rt);
	mlx_loop_hook(rt->mlbx->mlx, display, rt);
}

/* close the window and exit the program */
int	destroy(t_rt *rt)
{
	mlx_destroy_window(rt->mlbx->mlx, rt->mlbx->mlx_win);
	// to_free(rt, 'M'); //free the window
	exit(0);
	return (0);
}

/* updates the displayed image */
int	display(t_rt *rt)
{
	background(rt);
	mlx_put_image_to_window(rt->mlbx->mlx, rt->mlbx->mlx_win, rt->mlbx->img.img, 0, 0);
	return (0);
}

/* draws a pixel at (x, y) in color */
void	my_mlx_pixel_put(t_rt *rt, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < rt->win_w && y >= 0 && y < rt->win_h)
	{
		dst = rt->mlbx->img.addr + (y * rt->mlbx->img.line_length + \
		x * (rt->mlbx->img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

/* draws the background of the map */
void	background(t_rt	*rt)
{
	int	height;
	int	width;

	height = -1;
	while (++height < rt->win_h)
	{
		width = -1;
		while (++width < rt->win_w)
		{
			my_mlx_pixel_put(rt, width, height, 0xfffafa);
		}
	}
}
