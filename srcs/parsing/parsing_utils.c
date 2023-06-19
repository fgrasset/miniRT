#include "../../incs/minirt.h"

int count_elements(char *line)
{
	char **tab;
    int count;

	count = 0;
	tab = ft_split(line, ' ');
    while (tab != NULL) {
        count++;
    }
	free (line);
	free (tab);
    return count;
}
