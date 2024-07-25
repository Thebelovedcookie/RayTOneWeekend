/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonouelg <sonouelg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 21:28:56 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/25 13:29:46 by sonouelg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <math.h>
# include "type.h"
# include <limits.h>

# define EPSILON 0.000001

typedef struct s_scene
{
	t_ambilight	ambi;
	t_camera	cam;
	t_light		light;
	t_sphere	**tab_sp;
	t_plane		**tab_pl;
	t_cylindre	**tab_cy;
	int			fd;
	int			nb_object;
}				t_scene;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		line_length;
	int		bbp;
	int		endian;
}				t_img;

typedef struct s_w
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		size_x;
	int		size_y;
	double	**tab_inter;
	t_hit	hit;
	t_ray	ray;
	t_img	img;
	t_scene	*scene;
}				t_w;

void		camera(t_w *w, t_camera *cam);
t_fvec3		get_ray_direction(t_camera *cam, double x, double y, t_w *w);

/**************************** FILE MANAGEMENT ******************************/

int			open_my_file(char *file_name);
t_scene		*read_my_file(int fd);
int			check_my_line(char *str, t_scene *scene);

/*************************** SCENE MANAGEMENT ******************************/

//init scene
t_scene		*create_scene(void);
t_sphere	*new_sphere(t_scene *scene);
t_plane		*new_plane(t_scene *scene);
t_cylindre	*new_cylindre(t_scene *scene);

//fill
void		fill_ambient_lightning(char *str, t_scene *scene);
void		fill_camera(char *str, t_scene *scene);
void		fill_light(char *str, t_scene *scene);
void		fill_sphere(char *str, t_sphere *sphere, t_scene *scene);
void		fill_plane(char *str, t_plane *plane, t_scene *scene);
void		fill_cylindre(char *str, t_cylindre *cylindre, t_scene *scene);

//utils and checking
void		check_space(char *tmp, int bool, char *str, t_scene *scene);
t_fvec3		create_fvec3(char **tmp, t_scene *scene, char *str);
t_vec3		create_vec3(char **tmp, t_scene *scene, char *str);
void		check_plane_value(t_plane *p, t_scene *scene, t_vec3 c, char *str);
void		check_cyl_val(t_cylindre *cy, t_scene *scene, t_vec3 c, char *str);

//add
void		add_sphere(char *str, t_scene *scene);
void		add_plane(char *str, t_scene *scene);
void		add_cylinder(char *str, t_scene *scene);

/*************************** w MANAGEMENT ******************************/

void		create_w(t_scene *scene, t_w *w);

//hook
int			close_via_escape(int keycode, void *param);
int			close_via_cross(void *param);

/*************************** RENDER MANAGEMENT ******************************/

int			render(void *param);
void		my_mlx_pixel_put(t_w *w, int x, int y, int color);
int			create_trgb(t_fvec3 color);
t_fvec3		get_color(t_w *w);
double		hit_sphere(t_w *w, t_sphere *sphere);
double		hit_plane(t_w *w, t_plane *plane);
void		intersect_function(t_w *w);
void		intersect_help(t_w *w);
void		add_to_tab(t_w *w, int index, int type_obj, double t);
t_fvec3		sphere_hitted(t_w *w);
int			hit(t_w *w);
void		init_tab(t_w *w);
t_fvec3		at(double t, t_w *w);
t_fvec3		plane_hitted(t_w *w);
double		hit_cylinder(t_w *w, t_cylindre *cylindre);
t_fvec3		cylinder_hitted(t_w *w);
double		hit_cylinder_shadow(t_w *w, t_cylindre *cylindre);

/*************************** MATH FORMULE     *******************************/

t_fvec3		cross(t_fvec3 a, t_fvec3 b);
t_fvec3		dmul(double a, t_fvec3 b);
t_fvec3		x_vec3(t_fvec3 a, t_fvec3 b);
t_fvec3		sum(t_fvec3 a, t_fvec3 b);
t_fvec3		dive(t_fvec3 a, double b);
t_fvec3		sub(t_fvec3 a, t_fvec3 b);
double		dot(t_fvec3 a, t_fvec3 b);
double		length(t_fvec3 a);
double		length_squared(t_fvec3 a);
t_fvec3		normalized(t_fvec3 a);
t_fvec3		negat(t_fvec3 a);
t_fvec3		normal_at(t_sphere *sphere, t_fvec3 point);

/*************************** PHONGFORMULE     *******************************/

t_fvec3		reflection(t_fvec3 in, t_fvec3 normal);
//sphere
t_fvec3		ambient(t_fvec3 color, t_material mat, t_w *w);
void		diffuse(t_fvec3 color, t_w *w, t_phong *phong);
void		specular(t_phong *phong, t_w *w);
t_fvec3		reflection(t_fvec3 in, t_fvec3 normal);	
void		material_plane(t_w *w, t_plane *plane);
t_fvec3		calc_cy_normal(t_cylindre *cylindre, t_fvec3 intersected_point);
void		material_cylind(t_cylindre *cylindre, t_w *w);

/*************************** SHADOW            *******************************/

int			intersect_function_shad(t_w *w);
int			intersect_shad_help(t_w *w);
double		hit_sphere_shadow(t_w *w, t_sphere *sphere);
double		hit_plane_shadow(t_w *w, t_plane *plane);

/*************************** ERROR MANAGEMENT *******************************/
void		error(char *error, t_scene *scene, char *str);
void		ex_malloc_fail(t_scene *scene);
void		error_w(void *mlx_ptr, t_scene *scene);

/*************************** MEMORY MANAGEMENT ******************************/
//free
void		free_scene(t_scene **scene);
void		free_all(t_w *w);
void		free_tab_cy(t_cylindre ***cylindre);
void		free_tab_sp(t_sphere ***sphere);
void		free_tab_pl(t_plane ***plane);
void		free_tab_inter(t_w *w);

/**************************** TEST MANAGEMENT ********************************/
void		print_scene(t_scene *scene);
void		print_vec3(t_fvec3 a, char *name);
#endif