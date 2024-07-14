/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:49:05 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/12 21:50:46 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_sphere(t_window *window, t_sphere *sphere)
{
	t_fvec3	vector_origin_center;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	vector_origin_center = minus_vec3(sphere->center,
			window->scene->cam.view_point);
	a = length_squared(window->ray.ray_direction);
	b = dot_product(window->ray.ray_direction, vector_origin_center);
	c = length_squared(vector_origin_center)
		- ((sphere->diameter / 2.0) * (sphere->diameter / 2.0));
	discriminant = b * b - (a * c);
	if (discriminant < 0.0)
		return (-1.0);
	return (b - sqrt(discriminant) / a);
}

t_fvec3	sphere_hitted(t_window *window)
{
	t_fvec3		vector;
	t_fvec3		vec_ratio;
	double		ratio;
	t_sphere	*sphere;

	sphere = *(window->scene->tab_sp);
	while (sphere->n_object != window->hit.nb_objet)
		sphere = sphere->next;
	vector = unit_vector(minus_vec3(at(window->hit.lowest_t, window),
				sphere->center));
	vector = double_x_vec3(0.5, (t_fvec3){vector.x + 1,
			vector.y + 1, vector.z + 1});
	vec_ratio = vector_cross_vec3(at(window->hit.lowest_t, window), vector);
	ratio = length(vec_ratio);
	return (double_x_vec3(window->scene->light.brightness,
			double_x_vec3(1.0 - ratio, sphere->color)));
}