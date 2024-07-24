/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:19:37 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/24 15:10:55 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_cylinder(t_w *w, t_cylindre *cylindre)
{
	t_var	v;

	v.n = normalized(w->ray.ray_direction);
	v.a = normalized(cylindre->axe);
	v.e = dot(cross(v.n, v.a), cross(sub(cylindre->center,
					w->ray.ray_origin), v.a));
	v.f = (dot(cross(v.n, v.a), cross(v.n, v.a)))
		* ((cylindre->diameter / 2) * (cylindre->diameter / 2));
	v.g = dot(v.a, v.a) * ((dot(sub(cylindre->center, w->ray.ray_origin),
					cross(v.n, v.a))) * (dot(sub(cylindre->center,
						w->ray.ray_origin), cross(v.n, v.a))));
	v.h = dot(cross(v.n, v.a), cross(v.n, v.a));
	if (v.f - v.g < EPSILON || v.h == 0)
		return (-1);
	v.d1 = (v.e - sqrt(v.f - v.g)) / v.h;
	v.d2 = (v.e + sqrt(v.f - v.g)) / v.h;
	v.t1 = dot(v.a, sub(dmul(v.d1, v.n),
				sub(cylindre->center, w->ray.ray_origin)));
	v.t2 = dot(v.a, sub(dmul(v.d2, v.n),
				sub(cylindre->center, w->ray.ray_origin)));
	if (v.t1 > EPSILON && v.t1 < cylindre->height)
		return (v.d1);
	if (v.t2 > EPSILON && v.t2 < cylindre->height)
		return (v.d2);
	return (-1);
}

double	intersect_cylinder(t_w *w, t_cylindre *cylindre)
{
	double	tab[3];
	double	lowest;
	int		i;

	tab[0] = hit_cylinder(w, cylindre);
	tab[1] = hit_disk_1(cylindre, w);
	tab[2] = hit_disk_2(cylindre, w);
	i = 0;
	lowest = INT_MAX;
	while (i < 3)
	{
		if (tab[i] > EPSILON && tab[i] < lowest)
			lowest = tab[i];
		i++;
	}
	if (lowest == INT_MAX)
		return (-1);
	return (lowest);
}

double	hit_disk_2(t_cylindre *cylindre, t_w *w)
{
	t_fvec3	disk_center;
	t_fvec3	a;
	t_fvec3	cy_direction;
	double	parallele;
	double	distance;

	cy_direction = normalized(cylindre->axe);
	disk_center = sum(sub(cylindre->center, w->ray.ray_origin),
			dmul(cylindre->height, cy_direction));
	parallele = dot(cy_direction, w->ray.ray_direction);
	if (parallele == 0)
		return (-1);
	distance = dot(cy_direction, disk_center) / parallele;
	a = sub(dmul(distance, w->ray.ray_direction),
			disk_center);
	if (dot(a, a) < ((cylindre->diameter / 2)
			* (cylindre->diameter / 2)))
		return (distance);
	return (-1);
}

double	hit_disk_1(t_cylindre *cylindre, t_w *w)
{
	double	distance;
	t_fvec3	a;
	t_fvec3	cy_direction;
	double	parallele;

	cy_direction = normalized(negat(cylindre->axe));
	parallele = dot(cy_direction, w->ray.ray_direction);
	if (parallele == 0)
		return (-1);
	distance = dot(cy_direction, sub(cylindre->center, w->ray.ray_origin)) / parallele;
	a = sub(dmul(distance, w->ray.ray_direction),
			sub(cylindre->center, w->ray.ray_light_origin));
	if (dot(a, a) < ((cylindre->diameter / 2)
			* (cylindre->diameter / 2)))
		return (distance);
	return (-1);
}
