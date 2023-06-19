/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgrasset <fgrasset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 10:08:24 by lfabbian          #+#    #+#             */
/*   Updated: 2023/06/19 11:23:03 by fgrasset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minirt.h"

void	initialize(t_rt *rt);


int	main(int argc, char **argv)
{
	// char	*file;
	t_rt	*rt;
	(void) argv;
	rt = malloc(sizeof(t_rt));
	if (argc == 2)
	{
		initialize(rt);
		make_window(rt);
	}
	else
		print_error("2 args needed");
 /*check if the given argument is in .rt*/

}

/* initialize the structure */
void	initialize(t_rt *rt)
{
	rt->win_h = 600;
	rt->win_w = 1000;
}

/*
Pour le parsing, faire un ft_atoi pour les double, un pour les vecteurs, ils exit si le format n'est pas correct
Puis GNL + slit + strcmp pour savoir comment les classer dans une futur struct ?

Ensuite j'imagine que pour placer un pixel, il faudra faire passer les infos par pleins de fonctions différentes
qui vont à chaqu fois modifier légèrement les données du pixel en fonctions d'autres paramètres.

Il faut apparemment plutôt utiliser des matrices de transformations

Idée pour les structures, en faire une par type d'élément.
Donc,t_camera, t_light, t_scenes, t_figures
Quoi que le gars a 25 struct wtf
*/
