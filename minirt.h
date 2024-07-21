/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 21:28:56 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/21 22:45:58 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "./libft/libft.h"
# include <math.h>
# include "type.h"
# include <limits.h>

typedef struct s_ambilight
{
	double	ratio;
	t_fvec3	color;
}				t_ambilight;

// typedef struct s_camera
// {
// 	t_fvec3	view_point;
// 	t_fvec3	normalize;
// 	double	fov;
// 	double	focal_length;
// 	t_fvec3	viewport_u;
// 	t_fvec3	viewport_v;
// 	t_fvec3	pixel_delta_u;
// 	t_fvec3	pixel_delta_v;
// 	t_fvec3	viewport_upper_left;
// 	t_fvec3	pixel00_loc;
// }				t_camera;

typedef struct s_camera
{
	t_fvec3	view_point;
	t_fvec3	normalize;
	double	fov;
	t_fvec3	forward;
	t_fvec3	right;
	t_fvec3	up;
	t_fvec3	w;
	t_fvec3	u;
	t_fvec3	v;
	t_fvec3	horiz;
	t_fvec3	verti;
	t_fvec3	lower_left_corner;
	t_fvec3	upper_left;
	double	theta;
	double	h;
	double	viewport_height;
	double	viewport_width;
}				t_camera;

typedef struct s_light
{
	t_fvec3	light_point;
	double	brightness;
	t_fvec3	ray_direction;
}				t_light;

typedef struct s_material
{
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}			t_material;

typedef struct s_sphere
{
	t_fvec3			center;
	t_fvec3			color;
	double			diameter;
	double			n_object;
	t_material		mat;
	struct s_sphere	*next;
}				t_sphere;

typedef struct s_plane
{
	t_fvec3			point;
	t_fvec3			normalize;
	t_fvec3			color;
	t_material		mat;
	double			n_object;
	struct s_plane	*next;
}				t_plane;

typedef struct s_cylindre
{
	t_fvec3				center;
	t_fvec3				normalize;
	t_fvec3				color;
	double				height;
	double				diameter;
	double				n_object;
	t_material			mat;
	struct s_cylindre	*next;
}				t_cylindre;

typedef struct s_scene
{
	t_ambilight	ambi;
	t_camera	cam;
	t_light		light;
	t_sphere	**tab_sp;
	t_plane		**tab_pl;
	t_cylindre	**tab_cy;
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

typedef struct s_ratio
{
	double	aspect_ratio;
	int		image_height;
	double	viewport_height;
	double	viewport_width;
}				t_ratio;

typedef struct s_ray
{
	t_fvec3	ray_origin;
	t_fvec3	ray_direction;
	t_fvec3	ray_light_origin;
	t_fvec3	ray_light_direction;
}				t_ray;

typedef struct s_hit
{
	double	nb_objet;
	double	lowest_t;
	double	type_objet;
	double	shad_nb_objet;
	double	shad_lowest_t;
	double	shad_type_objet;
}				t_hit;

typedef struct s_window
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		size_x;
	int		size_y;
	double	**tab_inter;
	t_hit	hit;
	t_ratio	ratio;
	t_ray	ray;
	t_img	img;
	t_scene	*scene;
}				t_window;

typedef struct s_phong
{
	t_material	mat;
	t_fvec3		normalv;
	t_fvec3		intersected_point;
	t_fvec3		vector_eye;
	t_fvec3		lightv;
	t_fvec3		ambient;
	t_fvec3		diffuse;
	t_fvec3		effective_color;
	t_fvec3		specular;
	int			shadow;
}				t_phong;

void		calc_base(t_window *window, t_camera *cam);
t_fvec3		get_ray_direction(t_camera *cam, double x, double y);

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
//add
void		add_sphere(char *str, t_scene *scene);
void		add_plane(char *str, t_scene *scene);
void		add_cylinder(char *str, t_scene *scene);

/*************************** WINDOW MANAGEMENT ******************************/

void		create_window(t_scene *scene, t_window *window);

//hook
int			close_via_escape(int keycode, void *param);
int			close_via_cross(void *param);

/*************************** RENDER MANAGEMENT ******************************/

int			render(void *param);
void		my_mlx_pixel_put(t_window *window, int x, int y, int color);
int			create_trgb(t_fvec3 color);
t_fvec3		get_color(t_window *window);
void		aspect_ratio(t_window *window);
double		hit_sphere(t_window *window, t_sphere *sphere);
double		hit_plane(t_window *window, t_plane *plane);
void		intersect_function(t_window *window);
t_fvec3		sphere_hitted(t_window *window);
int			hit(t_window *window);
void		init_tab(t_window *window);
t_fvec3		at(double t, t_window *window);
t_fvec3		plane_hitted(t_window *window);
double		hit_cylinder(t_window *window, t_cylindre *cylindre);
t_fvec3		cylinder_hitted(t_window *window);
void		camera(t_window *window);

/*************************** MATH FORMULE     *******************************/

t_fvec3		vector_cross_vec3(t_fvec3 a, t_fvec3 b);
t_fvec3		double_x_vec3(double a, t_fvec3 b);
t_fvec3		x_vec3(t_fvec3 a, t_fvec3 b);
t_fvec3		sum_vec3(t_fvec3 a, t_fvec3 b);
t_fvec3		divide_vec3(t_fvec3 a, double b);
t_fvec3		minus_vec3(t_fvec3 a, t_fvec3 b);
double		dot_product(t_fvec3 a, t_fvec3 b);
t_fvec3		minus_double_fvec3(t_fvec3 b, double a);
double		length(t_fvec3 a);
double		length_squared(t_fvec3 a);
t_fvec3		unit_vector(t_fvec3 a);
t_fvec3		negating_vec3(t_fvec3 a);
t_fvec3		normal_at(t_sphere *sphere, t_fvec3 point);

/*************************** PHONGFORMULE     *******************************/

t_fvec3		reflection(t_fvec3 in, t_fvec3 normal);
//sphere
t_fvec3		ambient(t_fvec3 color, t_material mat, t_window *window);
void		diffuse(t_fvec3 color, t_window *window, t_phong *phong);
void		specular(t_phong *phong, t_window *window);
t_fvec3		reflection(t_fvec3 in, t_fvec3 normal);	
void		material_plane(t_window *window, t_plane *plane);
t_fvec3		calculate_cylinder_normal(t_cylindre *cylindre, t_fvec3 intersected_point);
void		material_cylind(t_cylindre *cylindre, t_window *window);

/*************************** SHADOW            *******************************/

int			intersect_function_shad(t_window *window);
double		hit_sphere_shadow(t_window *window, t_sphere *sphere);
double		hit_plane_shadow(t_window *window, t_plane *plane);
int			hit_shadow(t_window *window);
t_fvec3		get_shadow(t_window *window);

/*************************** ERROR MANAGEMENT *******************************/
void		error(char *error, t_scene *scene);
void		ex_malloc_fail(t_scene *scene);
void		error_window(void *mlx_ptr, t_scene *scene);

/*************************** MEMORY MANAGEMENT ******************************/
//free
void		free_scene(t_scene *scene);
void		free_tab_cy(t_cylindre ***cylindre);
void		free_tab_sp(t_sphere ***sphere);
void		free_tab_pl(t_plane ***plane);

/**************************** TEST MANAGEMENT ********************************/
void		print_scene(t_scene *scene);
void		print_vec3(t_fvec3 a, char *name);
#endif