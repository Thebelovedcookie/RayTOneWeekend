/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonouelg <sonouelg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:30:53 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/25 13:17:36 by sonouelg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

typedef struct s_vec2
{
	double	x;
	double	y;
}				t_vec2;

typedef struct s_vec3
{
	int	r;
	int	g;
	int	b;
}				t_vec3;

typedef struct s_fvec3
{
	double	x;
	double	y;
	double	z;
}				t_fvec3;

typedef struct s_material
{
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
}			t_material;

typedef struct s_ambilight
{
	double	ratio;
	t_fvec3	color;
}				t_ambilight;

typedef struct s_camera
{
	t_fvec3	view_point;
	t_fvec3	normalize;
	double	fov;
	t_fvec3	right;
	t_fvec3	up;
	double	ratio;
	double	angle;
	double	len_opp;
}			t_camera;

typedef struct s_light
{
	t_fvec3	light_point;
	double	brightness;
	t_fvec3	ray_direction;
}				t_light;

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
	t_fvec3			dir;
	t_fvec3			color;
	t_material		mat;
	double			n_object;
	struct s_plane	*next;
}				t_plane;

typedef struct s_cylindre
{
	t_fvec3				center;
	t_fvec3				axe;
	t_fvec3				color;
	double				height;
	double				diameter;
	double				n_object;
	t_material			mat;
	struct s_cylindre	*next;
}				t_cylindre;

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
}				t_hit;

typedef struct s_var
{
	t_fvec3	n;
	t_fvec3	a;
	double	e;
	double	f;
	double	g;
	double	h;
	double	d1;
	double	d2;
	double	t1;
	double	t2;
}				t_var;

#endif