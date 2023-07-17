/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbian <lfabbian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 13:51:04 by lfabbian          #+#    #+#             */
/*   Updated: 2023/07/17 13:51:08 by lfabbian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minirt.h"

void	free_objects(t_rt *rt)
{
	t_objects	*obj;

	while (rt->sc->obj)
	{
		obj = rt->sc->obj->next;
		free(rt->sc->obj);
		rt->sc->obj = obj;
	}
}

void	free_structures(t_rt *rt)
{
	free_objects(rt);
	free (rt->sc);
	free (rt);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free (tab[i]);
			i++;
		}
		free (tab);
	}
}
