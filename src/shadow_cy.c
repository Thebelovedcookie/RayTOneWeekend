/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_cy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonouelg <sonouelg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:20:19 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/25 13:08:28 by sonouelg         ###   ########.fr       */
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
	if (v.f - v.g < EPSILON || v.h == 0)
		return (-1);
	v.d1 = (v.e - sqrt(v.f - v.g)) / v.h;
	v.t1 = dot(v.a, sub(dmul(v.d1, v.n),
				sub(cy->center, w->ray.ray_light_origin)));
	if (v.t1 > EPSILON && v.t1 < cy->height)
		return (v.d1);
	return (-1);
}
