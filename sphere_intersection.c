/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:49:05 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/19 23:04:17 by mmahfoud         ###   ########.fr       */
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

// t_fvec3	sphere_hitted(t_window *window)
// {
// 	t_fvec3		vector;
// 	t_fvec3		vec_ratio;
// 	double		ratio;
// 	t_sphere	*sphere;

// 	sphere = *(window->scene->tab_sp);
// 	while (sphere->n_object != window->hit.nb_objet)
// 		sphere = sphere->next;
// 	vector = unit_vector(minus_vec3(at(window->hit.lowest_t, window),
// 				sphere->center));
// 	vector = double_x_vec3(0.5, (t_fvec3){vector.x + 1,
// 			vector.y + 1, vector.z + 1});
// 	vec_ratio = vector_cross_vec3(at(window->hit.lowest_t, window), vector);
// 	ratio = length(vec_ratio);
// 	return (double_x_vec3(window->scene->light.brightness,
// 			double_x_vec3(1.0 - ratio, sphere->color)));
// }

void	material(t_sphere *sphere, t_window *window)
{
	sphere->mat.ambient = window->scene->ambi.ratio;
	sphere->mat.diffuse = 0.9;
	sphere->mat.specular = 0.3;
	sphere->mat.shininess = 200.0;
}

t_fvec3	sphere_hitted(t_window *window)
{
	t_phong		phong;
	t_sphere	*sphere;

	sphere = *(window->scene->tab_sp);
	while (sphere->n_object != window->hit.nb_objet)
		sphere = sphere->next;
	material(sphere, window);
	phong.mat = sphere->mat;
	phong.intersected_point = at(window->hit.lowest_t, window);
	phong.normalv = normal_at(sphere, phong.intersected_point);
	phong.ambient = ambient(sphere->color, sphere->mat, window);
	diffuse(sphere->color, window, &phong);
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
	return (sum_vec3(sum_vec3(phong.ambient,
				phong.diffuse), phong.specular));
}
