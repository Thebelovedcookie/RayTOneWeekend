/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:53:35 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/12 23:12:01 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_plane(t_window *window, t_plane *plane)
{
	t_fvec3	l;
	double	denominator;
	double	numerator;

	l = unit_vector(window->ray.ray_direction);
	numerator = dot_product(minus_vec3(plane->point, window->ray.ray_direction), plane->normalize);
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

t_fvec3	plane_hitted(t_window *window)
{
	t_plane	*plane;

	plane = *(window->scene->tab_pl);
	while (plane->n_object != window->hit.nb_objet)
		plane = plane->next;
	return (plane->color);
}