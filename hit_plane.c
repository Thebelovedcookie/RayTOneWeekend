/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:53:35 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/20 17:31:10 by mmahfoud         ###   ########.fr       */
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

void	material_plane(t_window *window, t_plane *plane)
{
	plane->mat.ambient = window->scene->ambi.ratio;
	plane->mat.diffuse = 0.9;
	plane->mat.specular = 0.1;
	plane->mat.shininess = 200.0;
}

t_fvec3	plane_hitted(t_window *window)
{
	t_phong		phong;
	t_plane		*plane;

	plane = *(window->scene->tab_pl);
	while (plane->n_object != window->hit.nb_objet)
		plane = plane->next;
	material_plane(window, plane);
	phong.shadow = 0;
	phong.mat = plane->mat;
	phong.intersected_point = at(window->hit.lowest_t, window);
	phong.normalv = plane->normalize;
	phong.ambient = ambient(plane->color, plane->mat, window);
	diffuse(plane->color, window, &phong);
	if (phong.shadow == 1)
		return (phong.ambient);
	if (phong.diffuse.x == 0.0 && phong.diffuse.y == 0.0 && phong.diffuse.z == 0.0)
	{
		phong.specular = (t_fvec3){0.0, 0.0, 0.0};
		return (sum_vec3(sum_vec3(phong.ambient,
					phong.diffuse), phong.specular));
	}
	phong.vector_eye = negating_vec3(window->ray.ray_direction);
	specular(&phong, window);
	return (sum_vec3(phong.ambient,
				phong.diffuse));
	return (sum_vec3(sum_vec3(phong.ambient,
				phong.diffuse), phong.specular));
}
