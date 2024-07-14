/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:52:52 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/14 12:38:36 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_cylinder(t_window *window, t_cylindre *cylindre)
{
	double	a;
	double	b;
	double	c;
	double	delta;
	double	denominator;
	double	t;

	t_fvec3	b_o;
	t_fvec3	unit;

	unit = unit_vector(window->ray.ray_direction);
	b_o = minus_vec3(cylindre->center, window->ray.ray_origin);

	a = dot_product(x_vec3(unit, cylindre->normalize),
			x_vec3(b_o, cylindre->normalize));
	b = dot_product(x_vec3(unit, cylindre->normalize),
			(x_vec3(unit, cylindre->normalize))) * ((cylindre->diameter / 2)
			* ((cylindre->diameter / 2)));
	c = 1 * ((dot_product(b_o, x_vec3(unit, cylindre->normalize))
				* (dot_product(b_o, x_vec3(unit, cylindre->normalize)))));
	denominator = dot_product(x_vec3(unit, cylindre->normalize),
			(x_vec3(unit, cylindre->normalize)));
	if (denominator == 0)
	{
		if (b - c < 0)
		{
			return (-1.0);
		}
		else
		{
			return (0);
		}
	}
	if (b - c < 0)
		printf("ATTENTION RACINE NEGATIVE\n");
	// 	return (-1.0);
	delta = (a - sqrt(b - c)) / (dot_product(x_vec3(unit, cylindre->normalize),
			(x_vec3(unit, cylindre->normalize))));
	t = dot_product(unit, at(delta, window));
	if (t > 0)
		return (t);
	return (-1);
	// printf("delta = %f, t = %f\n", delta, t);
	// if (t > 0 && t < cylindre->height)
	// 	return (delta);
	// return (-1);
}

t_fvec3	cylinder_hitted(t_window *window)
{
	// t_fvec3		vector;
	// t_fvec3		vec_ratio;
	// double		ratio;
	t_cylindre	*cylindre;

	cylindre = *(window->scene->tab_cy);
	while (cylindre->n_object != window->hit.nb_objet)
		cylindre = cylindre->next;
	return (cylindre->color);
	// vector = unit_vector(minus_vec3(at(window->hit.lowest_t, window),
	// 			cylindre->center));
	// vector = double_x_vec3(0.5, (t_fvec3){vector.x + 1,
	// 		vector.y + 1, vector.z + 1});
	// vec_ratio = vector_cross_vec3(at(window->hit.lowest_t, window), vector);
	// ratio = length(vec_ratio);
	// return (double_x_vec3(window->scene->light.brightness,
	// 		double_x_vec3(1.0 - ratio, cylindre->color)));
}
