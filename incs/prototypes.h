#ifndef PROTOTYPES_H
# define PROTOTYPES_H
# include "minirt.h"

/* ERROR HANDLING */
int			print_error(char *error_message);

/* PARSING */
void		file_parsing(char *file, t_rt *rt);
char		*clean_line(char *line);
int			count_elements(char **tab);

void		check_filename(char *file);
void		line_parsing(int fd, char *line, t_rt *rt);

void		ambiance_parsing(char *line, t_rt *rt);
void		light_parsing(char *line, t_rt *rt);
void		camera_parsing(char *line, t_rt *rt);

void		objects_parsing(char *line, t_rt *rt);

t_objects	*last_object(t_objects	*lst);
void		object_add_end(t_objects **lst, t_objects *new);
int			number_objects(t_objects *lst);

int			is_float(char *str);
bool		is_color(char *str);
int			is_positive(char *str);
int			is_range(float number);

float		s_to_f(char *str);
float		parse_ratio(char *str, float ratio);
t_color		parse_color(char *line, t_color colors);
t_v3d		parse_coord(char *line, t_v3d points);
t_v3d		parse_vector(char *line, t_v3d points);
float		parse_other(char *line, float element, int i);

/* MAKE WINDOW */
void		make_window(t_rt *rt);
void		my_mlx_pixel_put(t_img img, int x, int y, int color);

/* RAYS */
void		launch_rays(t_rt *rt);
t_inter		*closest_inter(t_rt *rt, t_ray *ray);
t_inter		*intersect_plane(t_ray *ray, t_plane *plane);
t_inter		*intersect_sphere(t_ray *ray, t_sphere *sphere);
t_inter		*intersect_cylinder(t_ray *ray, t_cylinder *cylinder);
int			is_point_in_object(t_rt *rt, t_v3d *point);


/* v3d */
t_v3d		new_v3d(double x, double y, double z);
t_v3d		add(t_v3d a, t_v3d b);
t_v3d		sub(t_v3d a, t_v3d b);
t_v3d		sc_mult(t_v3d a, double nb);
double		norme(t_v3d a);
t_v3d		cross(t_v3d a, t_v3d b);
t_v3d		normalize(t_v3d	a);
t_v3d		mult(t_v3d a, t_v3d b);

/* v4d */
t_v4d		new_v4d(double x, double y, double z, double w);
t_v4d		v4d_from_v3d(t_v3d v, double w);
t_v3d		v4d_to_v3d(t_v4d v);
t_v4d		mat4_mul_v4d(t_mat4 m, t_v4d v);


/* MATH */
double		quad(double a, double b, double c);
double		dot_product(t_v3d a, t_v3d b);
int			rgb_to_int(t_color rgb);
t_mat4		mat4_translation(t_v3d t);
t_mat4		mat4_identity(void);
t_mat4		get_view_transform(t_camera cam);
t_mat4		get_inverse_view_transform(t_camera cam);
t_v3d		mat4_mul_v3d(t_mat4 m, t_v3d v);


/* UTILS 	*/
int			cmp(const char *s1, const char *s2);
void		print_v3d(t_v3d vect);
void		print_inter(t_inter *inter);

/* FREE */
void		free_structures(t_rt *rt);
void		free_tab(char **tab);
void		free_objects(t_rt *rt);

#endif
