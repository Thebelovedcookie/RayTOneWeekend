/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:49:05 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/24 14:00:10 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_sphere(t_w *w, t_sphere *sphere)
{
	t_fvec3	vector_origin_center;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	vector_origin_center = sub(sphere->center,
			w->scene->cam.view_point);
	a = length_squared(w->ray.ray_direction);
	b = dot(w->ray.ray_direction, vector_origin_center);
	c = length_squared(vector_origin_center)
		- ((sphere->diameter / 2.0) * (sphere->diameter / 2.0));
	discriminant = b * b - (a * c);
	if (discriminant < EPSILON)
		return (-1.0);
	return (b - sqrt(discriminant) / a);
}

void	material(t_sphere *sphere, t_w *w)
{
	sphere->mat.ambient = w->scene->ambi.ratio;
	sphere->mat.diffuse = 0.9;
	sphere->mat.specular = 0.3;
	sphere->mat.shininess = 200.0;
}

t_fvec3	sphere_hitted(t_w *w)
{
	t_phong		phong;
	t_sphere	*sphere;

	sphere = *(w->scene->tab_sp);
	while (sphere->n_object != w->hit.nb_objet)
		sphere = sphere->next;
	material(sphere, w);
	phong.mat = sphere->mat;
	phong.intersected_point = at(w->hit.lowest_t, w);
	phong.normalv = normal_at(sphere, phong.intersected_point);
	phong.ambient = ambient(sphere->color, sphere->mat, w);
	diffuse(sphere->color, w, &phong);
	if ((phong.diffuse.x == 0.0 && phong.diffuse.y == 0.0
			&& phong.diffuse.z == 0.0) || phong.shadow == 1)
		return (phong.ambient);
	phong.vector_eye = negat(w->ray.ray_direction);
	specular(&phong, w);
	return (sum(sum(phong.ambient,
				phong.diffuse), phong.specular));
}
