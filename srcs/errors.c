#include "../incs/minirt.h"

int	print_error(char *error_message)
{
	ft_printf("\033[31m%s\033[30m\n", error_message);
	exit (EXIT_FAILURE);
}
