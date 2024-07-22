/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 10:52:52 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/22 17:35:32 by mmahfoud         ###   ########.fr       */
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
	double	d1;
	double	t1;

	n = normalized(window->ray.ray_direction);
	a = normalized(cylindre->normalize);
	b = sub_vec(cylindre->center, window->ray.ray_origin);
	e = dot_product(cross_prod(n, a), cross_prod(b, a));
	f = (dot_product(cross_prod(n, a), cross_prod(n, a))) * ((cylindre->diameter / 2) * (cylindre->diameter / 2));
	g = dot_product(a, a) * ((dot_product(b, cross_prod(n, a))) * (dot_product(b, cross_prod(n, a))));
	h = dot_product(cross_prod(n, a), cross_prod(n, a));
	if (f - g < 0 || h == 0)
		return (-1);
	d1 = (e - sqrt(f - g)) / h;
	t1 = dot_product(a, sub_vec(double_x_vec3(d1, n), b));
	if (t1 > 0 && t1 < cylindre->height)
		return (d1);
	return (-1);
}


double	intersect_cylinder(t_window *window, t_cylindre *cylindre)
{
	double	tab[3];
	double	lowest;
	int		i;
	
	tab[0] = hit_cylinder(window, cylindre);
	tab[1] = hit_disk_1(cylindre, window); //disk bas
	tab[2] = hit_disk_2(cylindre, window); //disk haut
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

double	hit_disk_2(t_cylindre *cylindre, t_window *window)
{
	t_fvec3 disk_center;
	t_fvec3	inter;
	double	t;
	double	denom;
	
	disk_center = sum_vec3(cylindre->center, double_x_vec3(cylindre->height, cylindre->normalize));
	denom = dot_product(cylindre->normalize, window->ray.ray_direction);
    if (fabs(denom) > 0.000001)
	{
		t = dot_product(sub_vec(disk_center, window->ray.ray_origin), cylindre->normalize) / denom;
		if (t >= 0)
		{
            inter = sum_vec3(window->ray.ray_origin, double_x_vec3(t, window->ray.ray_direction));
			if (length(sub_vec(inter, disk_center)) <= (cylindre->diameter / 2))
                return (length(sub_vec(inter, disk_center)));
		}
	}
	return (0);
}

double	hit_disk_1(t_cylindre *cylindre, t_window *window)
{
	t_fvec3	inter;
	double	denom;
	double	t;

    denom = dot_product(negating_vec3(cylindre->normalize), window->ray.ray_direction);
    if (fabs(denom) > 0.000001)
	{
		t = dot_product(sub_vec(cylindre->center, window->ray.ray_origin), negating_vec3(cylindre->normalize)) / denom;
		if (t >= 0)
		{
            inter = sum_vec3(window->ray.ray_origin, double_x_vec3(t, window->ray.ray_direction));
			if (length(sub_vec(inter, cylindre->center)) <= (cylindre->diameter / 2))
                return (length(sub_vec(inter, cylindre->center)));
		}
	}
    return (0);
}

void material_cylind(t_cylindre *cylindre, t_window *window)
{
	cylindre->mat.ambient = window->scene->ambi.ratio;
	cylindre->mat.diffuse = 0.9;
	cylindre->mat.specular = 0.3;
	cylindre->mat.shininess = 200.0;
}

t_fvec3 calculate_cylinder_normal(t_cylindre *cylindre, t_fvec3 intersected_point)
{
	t_fvec3	base_to_intersection;
	t_fvec3	projection;
	t_fvec3	normal;
	double	projection_length;

	base_to_intersection = sub_vec(intersected_point, cylindre->center);
	projection_length = dot_product(base_to_intersection, cylindre->normalize);
	projection = double_x_vec3(projection_length, cylindre->normalize);
	normal = sub_vec(base_to_intersection, projection);
	return (normalized(normal));
}

t_fvec3	cylinder_hitted(t_window *window)
{
	t_cylindre	*cylindre;
	t_phong		phong;

	cylindre = *(window->scene->tab_cy);
	while (cylindre->n_object != window->hit.nb_objet)
		cylindre = cylindre->next;
	material_cylind(cylindre, window);
	phong.mat = cylindre->mat;
	phong.intersected_point = at(window->hit.lowest_t, window);
	phong.normalv = calculate_cylinder_normal(cylindre, phong.intersected_point);
	phong.ambient = ambient(cylindre->color, cylindre->mat, window);
	diffuse(cylindre->color, window, &phong);
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
	// return (sum_vec3(phong.ambient,
	// 			phong.diffuse));
	return (sum_vec3(sum_vec3(phong.ambient,
				phong.diffuse), phong.specular));
}
