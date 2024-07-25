/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:19:37 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/24 21:10:28 by mmahfoud         ###   ########.fr       */
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
