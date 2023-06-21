#include "../../incs/minirt.h"

void	check_filename(char *file);
void	line_parsing(int fd, char *line, t_rt *rt);

int		ambiance_parsing(char *line, t_rt *rt);
int		light_parsing(char *line, t_rt *rt);
int		camera_parsing(char *line, t_rt *rt);

void	plane_parsing(char *line, t_rt *rt);
void	sphere_parsing(char *line, t_rt *rt);
void	cylinder_parsing(char *line, t_rt *rt);


void	file_parsing(char *file, t_rt *rt)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		print_error("File error");
	check_filename(file);
	line = get_next_line(fd);
	if (!line)
		print_error("Empty file");
	line_parsing(fd, line, rt);
	close (fd);
}

void	line_parsing(int fd, char *line, t_rt *rt)
{
	int	count[3];

	ft_memset(count, 0, sizeof(count));
	while (line)
	{
		free (line);
		if (!ft_strncmp(line, "A ", 2))
			count[0] += ambiance_parsing(line, rt);
		else if (!ft_strncmp(line, "C ", 2))
			count[1] += camera_parsing(line, rt);
		else if (!ft_strncmp(line, "L ", 2))
			count[2] += light_parsing(line, rt);
		else if (!ft_strncmp(line, "pl ", 3))
			plane_parsing(line, rt);
		else if (!ft_strncmp(line, "sp ", 3))
			sphere_parsing(line, rt);
		else if (!ft_strncmp(line, "cy ", 3))
			cylinder_parsing(line, rt);
		else
			print_error("A type is not well defined");
		if (count[0] > 1 || count[1] > 1 || count[2] > 1)
			print_error("Too many cameras, lights or ambient lights");
		line = get_next_line(fd);
	}
}

void	check_filename(char *file)
{
	int	len;

	len = ft_strlen(file) - 1;
	if (!(file[len - 2] == '.' && file[len - 1] == 'r' && file[len] == 't'))
		print_error("Wrong scene format");
}
