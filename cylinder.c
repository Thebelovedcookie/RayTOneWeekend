/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:52:52 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/21 23:07:13 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_cylinder(t_window *window, t_cylindre *cylindre)
{
	t_fvec3 n;
	t_fvec3	a;
	t_fvec3	b;
	double	e;
	double	f;
	double	g;
	double	h;
	double	d;
	double	t;

	n = unit_vector(window->ray.ray_direction);
	a = unit_vector(cylindre->normalize);
	b = minus_vec3(cylindre->center, window->ray.ray_origin);
	e = dot_product(vector_cross_vec3(n, a), vector_cross_vec3(b, a));
	f = (dot_product(vector_cross_vec3(n, a), vector_cross_vec3(n, a))) * ((cylindre->diameter / 2) * (cylindre->diameter / 2));
	g = dot_product(a, a) * ((dot_product(b, vector_cross_vec3(n, a))) * (dot_product(b, vector_cross_vec3(n, a))));
	h = dot_product(vector_cross_vec3(n, a), vector_cross_vec3(n, a));
	// printf("h %f et f - g = %f\n", h, f-g);
	if (f - g < 0)
		return (-1);
	if (h == 0)
		return (-1);
	d = (e - sqrt(f - g)) / h;
	// printf("t = %f\n", t);
	t = dot_product(a, minus_vec3(double_x_vec3(d, n), b));
	if (t > 0 && t < cylindre->height)
		return (d);
	return (-1);
	// return (0);
}

void material_cylind(t_cylindre *cylindre, t_window *window)
{
	cylindre->mat.ambient = window->scene->ambi.ratio;
	cylindre->mat.diffuse = 0.9;
	cylindre->mat.specular = 0.1;
	cylindre->mat.shininess = 200.0;
}

t_fvec3 calculate_cylinder_normal(t_cylindre *cylindre, t_fvec3 intersected_point)
{
	t_fvec3	base_to_intersection;
	t_fvec3	projection;
	t_fvec3	normal;
	double	projection_length;

	base_to_intersection = minus_vec3(intersected_point, cylindre->center);
	projection_length = dot_product(base_to_intersection, cylindre->normalize);
	projection = double_x_vec3(projection_length, cylindre->normalize);
	normal = minus_vec3(base_to_intersection, projection);
	return (unit_vector(normal));
}

t_fvec3	cylinder_hitted(t_window *window)
{
	t_cylindre	*cylindre;
	t_phong		phong;

	(void)window;
	cylindre = *(window->scene->tab_cy);
	while (cylindre->n_object != window->hit.nb_objet)
		cylindre = cylindre->next;
	return (cylindre->color);
	material_cylind(cylindre, window);
	phong.shadow = 0;
	phong.mat = cylindre->mat;
	phong.intersected_point = at(window->hit.lowest_t, window);
	phong.normalv = calculate_cylinder_normal(cylindre, phong.intersected_point);
	phong.ambient = ambient(cylindre->color, cylindre->mat, window);
	diffuse(cylindre->color, window, &phong);
	// if (phong.shadow == 1)
	// 	return (phong.ambient);
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
