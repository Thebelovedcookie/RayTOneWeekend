/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:19:14 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/24 21:11:25 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	intersect_function_shad(t_w *w)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylindre	*cylind;

	sphere = *(w->scene->tab_sp);
	while (sphere)
	{
		if (hit_sphere_shadow(w, sphere) >= EPSILON)
			return (0);
		sphere = sphere->next;
	}
	plane = *(w->scene->tab_pl);
	while (plane)
	{
		if (hit_plane_shadow(w, plane) >= EPSILON)
			return (1);
		plane = plane->next;
	}
	cylind = *(w->scene->tab_cy);
	while (cylind)
	{
		if (hit_cylinder_shadow(w, cylind) >= EPSILON)
			return (0);
		cylind = cylind->next;
	}
	return (1);
}

double	hit_sphere_shadow(t_w *w, t_sphere *sphere)
{
	t_fvec3	vector_origin_center;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	vector_origin_center = sub(sphere->center,
			w->ray.ray_light_origin);
	a = length_squared(w->ray.ray_light_direction);
	b = dot(w->ray.ray_light_direction, vector_origin_center);
	c = length_squared(vector_origin_center)
		- ((sphere->diameter / 2.0) * (sphere->diameter / 2.0));
	discriminant = b * b - (a * c);
	if (discriminant < EPSILON)
		return (-1.0);
	return (b - sqrt(discriminant) / a);
}

double	hit_plane_shadow(t_w *w, t_plane *plane)
{
	t_fvec3	l;
	double	denominator;
	double	numerator;

	l = normalized(w->ray.ray_light_direction);
	numerator = dot(sub(plane->point,
				w->ray.ray_light_direction), plane->dir);
	denominator = dot(l, plane->dir);
	if (denominator == 0)
	{
		if (numerator == 0)
			return (0);
		return (-1);
	}
	else
		return (numerator / denominator);
}
