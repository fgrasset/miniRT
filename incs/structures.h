/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfabbian <lfabbian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 09:33:47 by lfabbian          #+#    #+#             */
/*   Updated: 2023/06/19 10:07:15 by lfabbian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include "minirt.h"

/* --------------------------------------------------- */
/* ----------- GLOBAL & USEFUL STRUCTURES ------------ */
/* --------------------------------------------------- */

typedef struct s_color
{
	int		red;
	int		green;
	int		blue;
} t_color;

typedef struct s_initc
{
	float	x;
	float	y;
	float	z;
} t_initc;

typedef struct s_direction
{
	float	x;
	float	y;
	float	z;

} t_direction;

/* --------------------------------------------------- */
/* --------- STRUCTURES RELATED TO THE SCENE --------- */
/* --------------------------------------------------- */

/* Linked list for all the objects in the scene */
typedef struct s_objects
{
	struct s_objects *next;
} t_objects;

typedef struct s_ambiant
{
	char	*id;
	float	ratio;
	t_color color;

} t_ambiant;

typedef struct s_camera
{
	char	*id;
	t_initc	init;

} t_camera;

typedef struct s_light
{
	char	*id;
	float	ratio;
	t_initc	init;

} t_light;


/* A scene is defined by some objects, two lights (ambiant & point of light) & one camera */
typedef struct s_scene
{
	t_ambiant	ambiant;
	t_camera	camera;
	t_light		light;
	t_objects	*objects;
} t_scene;

/* --------------------------------------------------- */

#endif
