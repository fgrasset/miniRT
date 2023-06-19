/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbian <lfabbian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 17:06:20 by lfabbian          #+#    #+#             */
/*   Updated: 2023/06/19 10:21:09 by lfabbian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minirt.h"

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
