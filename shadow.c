/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:52:52 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/19 21:14:56 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	intersect_function_shad(t_window *window)
{
	t_sphere	*sphere;
	t_plane		*plane;
	// t_cylindre	*cylind;
	double		t;

	init_tab(window);
	sphere = *(window->scene->tab_sp);
	while (sphere)
	{
		t = hit_sphere_shadow(window, sphere);
		if (t >= 0.0)
		{
			return (0);
		}
		sphere = sphere->next;
	}
	plane = *(window->scene->tab_pl);
	while (plane)
	{
		t = hit_plane_shadow(window, plane);
		if (t >= 0.0)
			return (1);
		plane = plane->next;
	}
	// cylind = *(window->scene->tab_cy);
	// while (cylind)
	// {
	// 	t = hit_cylinder(window, cylind);
	// 	if (t >= 0)
	// 	{
	// 		add_to_tab(window, cylind->n_object, 3, t);
	// 	}
	// 	cylind = cylind->next;
	// }
	return (1);
}

double	hit_sphere_shadow(t_window *window, t_sphere *sphere)
{
	t_fvec3	vector_origin_center;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	vector_origin_center = minus_vec3(sphere->center,
			window->ray.ray_light_origin);
	a = length_squared(window->ray.ray_light_direction);
	b = dot_product(window->ray.ray_light_direction, vector_origin_center);
	c = length_squared(vector_origin_center)
		- ((sphere->diameter / 2.0) * (sphere->diameter / 2.0));
	discriminant = b * b - (a * c);
	if (discriminant < 0.0)
		return (-1.0);
	return (b - sqrt(discriminant) / a);
}

double	hit_plane_shadow(t_window *window, t_plane *plane)
{
	t_fvec3	l;
	double	denominator;
	double	numerator;

	l = unit_vector(window->ray.ray_light_direction);
	numerator = dot_product(minus_vec3(plane->point, window->ray.ray_light_direction), plane->normalize);
	denominator = dot_product(l, plane->normalize);
	if (denominator == 0)
	{
		if (numerator == 0)
		{
			return (0);
		}
		return (-1);
	}
	else
		return (numerator / denominator);
}

int	hit_shadow(t_window *window)
{
	int		i;

	i = 0;
	window->hit.lowest_t = INT_MAX;
	while (i < window->scene->nb_object)
	{
		if (window->tab_inter[i][1] > 0 && window->tab_inter[i][1] < window->hit.lowest_t)
		{
			window->hit.shad_type_objet = window->tab_inter[i][0];
			window->hit.shad_lowest_t = window->tab_inter[i][1];
			window->hit.shad_nb_objet = window->tab_inter[i][2];
		}
		i++;
	}
	if (window->hit.lowest_t == INT_MAX)
	{
		window->hit.lowest_t = 0;
		return (0);
	}
	return (1);
}

t_fvec3	get_shadow(t_window *window)
{
	if (hit(window))
	{
		if (window->hit.type_objet == 1)
			return (sphere_hitted(window));
		if (window->hit.type_objet == 2)
			return (plane_hitted(window));
		if (window->hit.type_objet == 3)
			return (cylinder_hitted(window));
	}
	return (double_x_vec3(window->scene->ambi.ratio,
			window->scene->ambi.color));
}
