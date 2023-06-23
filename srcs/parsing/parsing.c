#include "../../incs/minirt.h"

void	check_filename(char *file);
void	line_parsing(int fd, char *line, t_rt *rt);

int		ambiance_parsing(char **tab, t_rt *rt);
int		light_parsing(char **tab, t_rt *rt);
int		camera_parsing(char **tab, t_rt *rt);

void	objects_parsing(char **tab, t_rt *rt);
void	plane_parsing(char **tab, t_rt *rt);
void	sphere_parsing(char **tab, t_rt *rt);
void	cylinder_parsing(char **tab, t_rt *rt);


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
	char **tab;
	int	count[3];

	ft_memset(count, 0, sizeof(count));
	while (line)
	{
		free (line);
		tab = ft_split(line, ' ');
		if (!ft_strcmp(tab[0], "A"))
			count[0] = ambiance_parsing(tab, rt);
		else if (!ft_strcmp(tab[0], "C"))
			count[1] += camera_parsing(tab, rt);
		else if (!ft_strcmp(tab[0], "L"))
			count[2] += light_parsing(tab, rt);
		else if ((!ft_strcmp(tab[0], "pl")) || (!ft_strcmp(tab[0], "sp"))
			|| (!ft_strcmp(tab[0], "cy")))
			objects_parsing(tab, rt);
		else
			print_error("Something is not well defined");
		if (count[0] > 1 || count[1] > 1 || count[2] > 1)
				print_error("Too many cameras, lights or ambient lights");
		free(tab);
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
