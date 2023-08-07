#include "../incs/minirt.h"

int	main(int argc, char **argv)
{
	t_rt	*rt;

	(void) argv;
	rt = ft_calloc(sizeof(t_rt), 1);
	if (argc == 2)
	{
		file_parsing(argv[1], rt);
		make_window(rt);
		free_structures(rt);
	}
	else
	{
		ft_putstr_fd("\033[31m2 args needed :\n\033[0m", 2);
		ft_putstr_fd("\033[31m./miniRT [scene_path]\n\033[0m", 2);
	}
}
