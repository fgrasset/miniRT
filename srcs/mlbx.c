# include "../incs/minirt.h"

int		destroy(t_rt *rt);
int		display(t_rt *rt);
void	my_mlx_pixel_put(t_img img, int x, int y, int color);
void	background(t_rt	*rt);


/* creates the graphical window */
void	make_window(t_rt *rt)
{
	t_mlbx	*mlbx;

	mlbx = malloc(sizeof(t_mlbx));
	rt->mlbx = mlbx;
	rt->mlbx->mlx = mlx_init();
	rt->mlbx->mlx_win = mlx_new_window(mlbx->mlx,WIN_W, WIN_H, "MiniRT");
	rt->mlbx->img.img = mlx_new_image(mlbx->mlx, WIN_W, WIN_H);
	rt->mlbx->img.addr = mlx_get_data_addr(mlbx->img.img, &mlbx->img.bits_per_pixel, &mlbx->img.line_length, &mlbx->img.endian);
	mlx_hook(mlbx->mlx_win, 17, 0, destroy, rt);
	mlx_loop_hook(mlbx->mlx, display, rt);
	mlx_loop(mlbx->mlx);
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
void	my_mlx_pixel_put(t_img img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIN_W && y >= 0 && y < WIN_H)
	{
		dst = img.addr + (y * img.line_length + \
		x * (img.bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

/* draws the background of the map */
void	background(t_rt	*rt)
{
	int	height;
	int	width;

	height = -1;
	while (++height < WIN_H)
	{
		width = -1;
		while (++width < WIN_W)
		{
			my_mlx_pixel_put(rt->mlbx->img, width, height, 0x0000ff);
		}
	}
}
