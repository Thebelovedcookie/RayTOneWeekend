/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonouelg <sonouelg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 21:01:16 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/25 13:07:55 by sonouelg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	create_trgb(t_fvec3 color)
{
	t_vec3	color_int;

	color_int.r = color.x * 255;
	if (color_int.r > 255)
		color_int.r = 255;
	color_int.g = color.y * 255;
	if (color_int.g > 255)
		color_int.g = 255;
	color_int.b = color.z * 255;
	if (color_int.b > 255)
		color_int.b = 255;
	return (color_int.r << 16 | color_int.g << 8
		| color_int.b);
}

t_fvec3	at(double t, t_w *w)
{
	return (sum(w->scene->cam.view_point,
			dmul(t, w->ray.ray_direction)));
}

t_fvec3	get_color(t_w *w)
{
	if (hit(w))
	{
		if (w->hit.type_objet == 1)
			return (sphere_hitted(w));
		if (w->hit.type_objet == 2)
			return (plane_hitted(w));
		if (w->hit.type_objet == 3)
			return (cylinder_hitted(w));
	}
	return (dmul(w->scene->ambi.ratio,
			w->scene->ambi.color));
}

void	add_to_tab(t_w *w, int index, int type_obj, double t)
{
	w->tab_inter[index - 1][0] = type_obj;
	w->tab_inter[index - 1][1] = t;
	w->tab_inter[index - 1][2] = index;
}
