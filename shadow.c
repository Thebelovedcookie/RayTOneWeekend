/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:52:52 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/19 21:14:56 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	intersect_function_shad(t_window *window)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylindre	*cylind;
	double		t;

	init_tab(window);
	sphere = *(window->scene->tab_sp);
	while (sphere)
	{
		// printf("1\n");
		t = hit_sphere_shadow(window, sphere);
		if (t >= 0.0)
		{
			return (0);
		}
		sphere = sphere->next;
	}
	plane = *(window->scene->tab_pl);
	while (plane)
	{
		t = hit_plane_shadow(window, plane);
		if (t >= 0.0)
			return (1);
		plane = plane->next;
	}
	cylind = *(window->scene->tab_cy);
	while (cylind)
	{
		t = intersect_cylinder_shadow(window, cylind);
		if (t >= 0)
		{
			return (0);
		}
		cylind = cylind->next;
	}
	return (1);
}

// double	hit_cylinder_shadow(t_window *window, t_cylindre *cylindre)
// {
// 	t_fvec3 n;
// 	t_fvec3	a;
// 	t_fvec3	b;
// 	double	e;
// 	double	f;
// 	double	g;
// 	double	h;
// 	double	d1;
// 	double	d2;
// 	double	t1;
// 	double	t2;

// 	n = normalized(window->ray.ray_light_direction);
// 	a = normalized(cylindre->normalize);
// 	b = sub_vec(cylindre->center, window->ray.ray_light_origin);
// 	e = dot_product(cross_prod(n, a), cross_prod(b, a));
// 	f = (dot_product(cross_prod(n, a), cross_prod(n, a))) * ((cylindre->diameter / 2) * (cylindre->diameter / 2));
// 	g = dot_product(a, a) * ((dot_product(b, cross_prod(n, a))) * (dot_product(b, cross_prod(n, a))));
// 	h = dot_product(cross_prod(n, a), cross_prod(n, a));
// 	// printf("h %f et f - g = %f\n", h, f-g);
// 	if (f - g < 0)
// 		return (-1);
// 	if (h == 0)
// 		return (-1);
// 	d1 = (e - sqrt(f - g)) / h;
// 	d2 = (e + sqrt(f - g)) / h;
// 	// printf("d1 = %f d2 = %f\n", d1, d2);
// 	t1 = dot_product(a, sub_vec(double_x_vec3(d1, n), b));
// 	t2 = dot_product(a, sub_vec(double_x_vec3(d2, n), b));
// 	if (t1 > 0)
// 		return (d1);
// 	if (t2 > 0)
// 		return (d2);
// 	return (-1);
// }

double	hit_cylinder_shadow(t_window *window, t_cylindre *cylindre)
{
	t_fvec3 n;
	t_fvec3	a;
	t_fvec3	b;
	double	e;
	double	f;
	double	g;
	double	h;
	double	d1;
	double	t1;

	n = normalized(window->ray.ray_light_direction);
	a = normalized(cylindre->normalize);
	b = sub_vec(cylindre->center, window->ray.ray_light_origin);
	e = dot_product(cross_prod(n, a), cross_prod(b, a));
	f = (dot_product(cross_prod(n, a), cross_prod(n, a))) * ((cylindre->diameter / 2) * (cylindre->diameter / 2));
	g = dot_product(a, a) * ((dot_product(b, cross_prod(n, a))) * (dot_product(b, cross_prod(n, a))));
	h = dot_product(cross_prod(n, a), cross_prod(n, a));
	// printf("h %f et f - g = %f\n", h, f-g);
	if (f - g < 0)
		return (-1);
	if (h == 0)
		return (-1);
	d1 = (e - sqrt(f - g)) / h;
	// printf("d1 = %f d2 = %f\n", d1, d2);
	t1 = dot_product(a, sub_vec(double_x_vec3(d1, n), b));
	if (t1 > 0)
		return (d1);
	return (-1);
}

double	intersect_cylinder_shadow(t_window *window, t_cylindre *cylindre)
{
	double	tab[3];
	double	lowest;
	int		i;
	
	tab[0] = hit_cylinder_shadow(window, cylindre);
	tab[1] = hit_disk_1_shadow(cylindre, window);
	tab[2] = hit_disk_2_shadow(cylindre, window);
	i = 0;
	lowest = INT_MAX;
	while (i < 3)
	{
		if (tab[i] > 0 && tab[i] < lowest)
		{
			lowest = tab[i];
		}
		i++;
	}
	if (lowest == INT_MAX)
		return (-1);
	return (lowest);
}

double	hit_disk_2_shadow(t_cylindre *cylindre, t_window *window)
{
	t_fvec3 disk_center;
	t_fvec3	inter;
	double	t;
	double	denom;
	
	disk_center = sum_vec3(cylindre->center, double_x_vec3(cylindre->height, cylindre->normalize));
	denom = dot_product(cylindre->normalize, window->ray.ray_light_direction);
    if (fabs(denom) > 0.000001)
	{
		t = dot_product(sub_vec(disk_center, window->ray.ray_light_origin), cylindre->normalize) / denom;
		if (t > 0)
		{
            inter = sum_vec3(window->ray.ray_light_origin, double_x_vec3(t, window->ray.ray_light_direction));
			if (length(sub_vec(inter, disk_center)) <= (cylindre->diameter / 2))
                return (length(sub_vec(inter, disk_center)));
		}
	}
	return (0);
}

double	hit_disk_1_shadow(t_cylindre *cylindre, t_window *window)
{
	t_fvec3	inter;
	double	denom;
	double	t;

    denom = dot_product(cylindre->normalize, window->ray.ray_light_direction);
    if (fabs(denom) > 0.000001)
	{
		t = dot_product(sub_vec(cylindre->center, window->ray.ray_light_origin), cylindre->normalize) / denom;
		if (t > 0)
		{
            inter = sum_vec3(window->ray.ray_light_origin, double_x_vec3(t, window->ray.ray_light_direction));
			if (length(sub_vec(inter, cylindre->center)) <= (cylindre->diameter / 2))
                return (length(sub_vec(inter, cylindre->center)));
		}
	}
    return (0);
}


double	hit_sphere_shadow(t_window *window, t_sphere *sphere)
{
	t_fvec3	vector_origin_center;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	vector_origin_center = sub_vec(sphere->center,
			window->ray.ray_light_origin);
	a = length_squared(window->ray.ray_light_direction);
	b = dot_product(window->ray.ray_light_direction, vector_origin_center);
	c = length_squared(vector_origin_center)
		- ((sphere->diameter / 2.0) * (sphere->diameter / 2.0));
	discriminant = b * b - (a * c);
	if (discriminant < 0.0)
		return (-1.0);
	return (b - sqrt(discriminant) / a);
}

double	hit_plane_shadow(t_window *window, t_plane *plane)
{
	t_fvec3	l;
	double	denominator;
	double	numerator;

	l = normalized(window->ray.ray_light_direction);
	numerator = dot_product(sub_vec(plane->point, window->ray.ray_light_direction), plane->normalize);
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


