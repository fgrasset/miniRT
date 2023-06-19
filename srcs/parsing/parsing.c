#include "../../incs/minirt.h"

void parsing(char *file)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		print_error("File error");
	line = get_next_line(fd);
	if (!line)
		print_error("Empty file");
}
