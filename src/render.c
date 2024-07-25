/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonouelg <sonouelg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 21:01:16 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/25 13:26:36 by sonouelg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	my_mlx_pixel_put(t_w *w, int x, int y, int color)
{
	char	*dst;

	dst = w->img.addr + (y * w->img.line_length
			+ x * (w->img.bbp / 8));
	*(unsigned int *)dst = color;
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

void	intersect_function(t_w *w)
{
	t_sphere	*sphere;
	t_plane		*plane;
	double		t;

	init_tab(w);
	sphere = *(w->scene->tab_sp);
	while (sphere)
	{
		t = hit_sphere(w, sphere);
		if (t > EPSILON)
			add_to_tab(w, sphere->n_object, 1, t);
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
	intersect_help(w);
}

void	intersect_help(t_w *w)
{
	t_cylindre	*cylind;
	double		t;

	cylind = *(w->scene->tab_cy);
	while (cylind)
	{
		t = hit_cylinder(w, cylind);
		if (t > EPSILON)
			add_to_tab(w, cylind->n_object, 3, t);
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
