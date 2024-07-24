/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 21:01:16 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/24 15:11:56 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	create_trgb(t_fvec3 color)
{
	t_vec3	color_int;

	color_int.red = color.x * 255;
	if (color_int.red > 255)
		color_int.red = 255;
	color_int.green = color.y * 255;
	if (color_int.green > 255)
		color_int.green = 255;
	color_int.blue = color.z * 255;
	if (color_int.blue > 255)
		color_int.blue = 255;
	return (color_int.red << 16 | color_int.green << 8
		| color_int.blue);
}

void	my_mlx_pixel_put(t_w *w, int x, int y, int color)
{
	char	*dst;

	dst = w->img.addr + (y * w->img.line_length
			+ x * (w->img.bbp / 8));
	*(unsigned int *)dst = color;
}

t_fvec3	at(double t, t_w *w)
{
	return (sum(w->scene->cam.view_point,
			dmul(t, w->ray.ray_direction)));
}

void	add_to_tab(t_w *w, int index, int type_obj, double t)
{
	w->tab_inter[index - 1][0] = type_obj;
	w->tab_inter[index - 1][1] = t;
	w->tab_inter[index - 1][2] = index;
}

int	hit(t_w *w)
{
	int		i;

	i = 0;
	w->hit.lowest_t = INT_MAX;
	while (i < w->scene->nb_object)
	{
		if (w->tab_inter[i][1] > 0 && w->tab_inter[i][1] < w->hit.lowest_t)
		{
			w->hit.type_objet = w->tab_inter[i][0];
			w->hit.lowest_t = w->tab_inter[i][1];
			w->hit.nb_objet = w->tab_inter[i][2];
		}
		i++;
	}
	if (w->hit.lowest_t == INT_MAX)
	{
		w->hit.lowest_t = 0;
		return (0);
	}
	return (1);
}

t_fvec3	get_color(t_w *w)
{
	if (hit(w))
	{
		if (w->hit.type_objet == 1)
			return (sphere_hitted(w));
		if (w->hit.type_objet == 2)
			return (plane_hitted(w));
		if (w->hit.type_objet == 3)
			return (cylinder_hitted(w));
	}
	return (dmul(w->scene->ambi.ratio,
			w->scene->ambi.color));
}

void	intersect_function(t_w *w)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylindre	*cylind;
	double		t;

	init_tab(w);
	sphere = *(w->scene->tab_sp);
	while (sphere)
	{
		t = hit_sphere(w, sphere);
		if (t > EPSILON)
		{
			add_to_tab(w, sphere->n_object, 1, t);
		}
		sphere = sphere->next;
	}
	plane = *(w->scene->tab_pl);
	while (plane)
	{
		t = hit_plane(w, plane);
		if (t > EPSILON)
			add_to_tab(w, plane->n_object, 2, t);
		plane = plane->next;
	}
	cylind = *(w->scene->tab_cy);
	while (cylind)
	{
		t = intersect_cylinder(w, cylind);
		if (t > EPSILON)
		{
			add_to_tab(w, cylind->n_object, 3, t);
		}
		cylind = cylind->next;
	}
}

int	render(void *param)
{
	t_w		*w;
	int		x;
	int		y;
	t_fvec3	color;

	y = 0;
	w = (t_w *)param;
	w->ray.ray_origin = w->scene->cam.view_point;
	camera(w, &w->scene->cam);
	while (y < w->size_y)
	{
		x = 0;
		while (x < w->size_x)
		{
			w->ray.ray_direction = get_ray_direction(&w->scene->cam, x, y, w);
			intersect_function(w);
			color = get_color(w);
			my_mlx_pixel_put(w, x, y, create_trgb(color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(w->mlx_ptr, w->win_ptr, w->img.img_ptr, 0, 0);
	return (0);
}
