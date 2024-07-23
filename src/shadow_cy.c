/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_cy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:20:19 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/23 15:37:15 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_cylinder_shadow(t_w *w, t_cylindre *cy)
{
	t_var	v;

	v.n = normalized(w->ray.ray_light_direction);
	v.a = normalized(cy->axe);
	v.e = dot(cross(v.n, v.a), cross(sub(cy->center,
					w->ray.ray_light_origin), v.a));
	v.f = (dot(cross(v.n, v.a), cross(v.n, v.a)))
		* ((cy->diameter / 2) * (cy->diameter / 2));
	v.g = dot(v.a, v.a) * ((dot(sub(cy->center, w->ray.ray_light_origin),
					cross(v.n, v.a))) * (dot(sub(cy->center,
						w->ray.ray_light_origin), cross(v.n, v.a))));
	v.h = dot(cross(v.n, v.a), cross(v.n, v.a));
	if (v.f - v.g < 0 || v.h == 0)
		return (-1);
	v.d1 = (v.e - sqrt(v.f - v.g)) / v.h;
	v.d2 = (v.e + sqrt(v.f - v.g)) / v.h;
	v.t1 = dot(v.a, sub(dmul(v.d1, v.n),
				sub(cy->center, w->ray.ray_light_origin)));
	v.t2 = dot(v.a, sub(dmul(v.d2, v.n),
				sub(cy->center, w->ray.ray_light_origin)));
	if (v.t1 > 0.0 && v.t1 < cy->height)
		return (v.d1);
	if (v.t2 > 0.0 && v.t2 < cy->height)
		return (v.d2);
	return (-1);
}

double	intersect_cylinder_shadow(t_w *w, t_cylindre *cylindre)
{
	double	tab[3];
	double	lowest;
	int		i;

	tab[0] = hit_cylinder_shadow(w, cylindre);
	tab[1] = hit_disk_1_shadow(cylindre, w);
	tab[2] = hit_disk_2_shadow(cylindre, w);
	i = 0;
	lowest = INT_MAX;
	while (i < 3)
	{
		if (tab[i] > 0 && tab[i] < lowest)
			lowest = tab[i];
		i++;
	}
	if (lowest == INT_MAX)
		return (-1);
	return (lowest);
}

double	hit_disk_2_shadow(t_cylindre *cylindre, t_w *w)
{
	t_fvec3	disk_center;
	t_fvec3	a;
	t_fvec3	cy_direction;
	double	paralelle;
	double	distance;

	cy_direction = normalized(cylindre->axe);
	disk_center = sum(sub(cylindre->center, w->ray.ray_light_origin),
			dmul(cylindre->height, cy_direction));
	paralelle = dot(cy_direction, w->ray.ray_light_direction);
	if (paralelle == 0)
		return (-1);
	distance = dot(cy_direction, disk_center) / paralelle;
	a = sub(dmul(distance, w->ray.ray_light_direction),
			disk_center);
	if (dot(a, a) < ((cylindre->diameter / 2)
			* (cylindre->diameter / 2)))
		return (distance);
	return (-1);
}

double	hit_disk_1_shadow(t_cylindre *cylindre, t_w *w)
{
	double	distance;
	t_fvec3	a;
	double	parallele;
	t_fvec3	cy_direction;

	cy_direction = normalized(negat(cylindre->axe));
	parallele = dot(cy_direction, w->ray.ray_light_direction);
	if (parallele == 0)
		return (-1);
	distance = dot(cy_direction, sub(cylindre->center, w->ray.ray_light_origin)) / parallele;
	a = sub(dmul(distance,
				w->ray.ray_light_direction), sub(cylindre->center, w->ray.ray_light_origin));
	if (dot(a, a) < ((cylindre->diameter / 2)
			* (cylindre->diameter / 2)))
		return (distance);
	return (-1);
}
