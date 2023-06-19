
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

typedef struct s_vec3d
{
	double	x;
	double	y;
	double	z;
} t_vec3d;

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
	t_vec3d	init;

} t_camera;

typedef struct s_light
{
	char	*id;
	float	ratio;
	t_vec3d	init;

} t_light;


/* A scene is defined by some objects, two lights (ambiant & point of light) & one camera */
typedef struct s_scene
{
	t_ambiant	ambiant;
	t_camera	camera;
	t_light		light;
	t_objects	*objects;
} t_scene;

/* struct for the image of mlbx */
typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_img;


/* struct for everything mlbx related */
typedef struct s_mlbx
{
	void	*mlx;
	void	*mlx_win;
	t_img	img;
} t_mlbx;

/* --------------------------------------------------- */

#endif
