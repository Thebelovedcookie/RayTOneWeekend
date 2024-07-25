/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 11:59:21 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/24 21:17:59 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	material_cylind(t_cylindre *cylindre, t_w *w)
{
	cylindre->mat.ambient = w->scene->ambi.ratio;
	cylindre->mat.diffuse = 0.9;
	cylindre->mat.specular = 0.3;
	cylindre->mat.shininess = 200.0;
}

t_fvec3	calc_cy_normal(t_cylindre *cylindre, t_fvec3 intersected_point)
{
	t_fvec3	base_to_intersection;
	t_fvec3	projection;
	t_fvec3	normal;
	double	projection_length;

	base_to_intersection = sub(intersected_point, cylindre->center);
	projection_length = dot(base_to_intersection, cylindre->axe);
	projection = dmul(projection_length, cylindre->axe);
	normal = sub(base_to_intersection, projection);
	return (normalized(normal));
}

t_fvec3	cylinder_hitted(t_w *w)
{
	t_cylindre	*cylindre;
	t_phong		phong;

	cylindre = *(w->scene->tab_cy);
	while (cylindre->n_object != w->hit.nb_objet)
		cylindre = cylindre->next;
	material_cylind(cylindre, w);
	phong.shadow = 0;
	phong.mat = cylindre->mat;
	phong.intersected_point = at(w->hit.lowest_t, w);
	phong.normalv = calc_cy_normal(cylindre, phong.intersected_point);
	phong.ambient = ambient(cylindre->color, cylindre->mat, w);
	diffuse(cylindre->color, w, &phong);
	if (phong.shadow == 1 || (phong.diffuse.x == 0.0
			&& phong.diffuse.y == 0.0 && phong.diffuse.z == 0.0))
		return (phong.ambient);
	phong.vector_eye = negat(w->ray.ray_direction);
	specular(&phong, w);
	return (sum(sum(phong.ambient,
				phong.diffuse), phong.specular));
}
