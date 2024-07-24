/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:53:35 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/24 15:01:25 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_plane(t_w *w, t_plane *plane)
{
	t_fvec3	l;
	double	denominator;
	double	numerator;

	l = normalized(w->ray.ray_direction);
	numerator = dot(sub(plane->point, w->ray.ray_direction), plane->normalize);
	denominator = dot(l, plane->normalize);
	if (denominator == 0)
	{
		if (numerator == 0)
			return (0);
		return (-1);
	}
	else
		return (numerator / denominator);
}

void	material_plane(t_w *w, t_plane *plane)
{
	plane->mat.ambient = w->scene->ambi.ratio;
	plane->mat.diffuse = 0.9;
	plane->mat.specular = 0.9;
	plane->mat.shininess = 200.0;
}

t_fvec3	plane_hitted(t_w *w)
{
	t_phong		phong;
	t_plane		*plane;

	plane = *(w->scene->tab_pl);
	while (plane->n_object != w->hit.nb_objet)
		plane = plane->next;
	material_plane(w, plane);
	phong.mat = plane->mat;
	phong.intersected_point = at(w->hit.lowest_t, w);
	phong.normalv = plane->normalize;
	phong.ambient = ambient(plane->color, plane->mat, w);
	diffuse(plane->color, w, &phong);
	if ((phong.diffuse.x == 0.0 && phong.diffuse.y == 0.0
			&& phong.diffuse.z == 0.0) || phong.shadow == 1)
		return (phong.ambient);
	phong.vector_eye = negat(w->ray.ray_direction);
	specular(&phong, w);
	return (sum(phong.ambient, phong.diffuse));
}
