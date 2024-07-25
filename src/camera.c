/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonouelg <sonouelg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:51:31 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/25 12:45:05 by sonouelg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	camera(t_w *w, t_camera *cam)
{
	cam->ratio = w->size_x / w->size_y;
	cam->angle = (cam->fov * M_PI) / 180;
	cam->len_opp = tan(cam->angle / 2);
	cam->right = dmul(cam->len_opp,
			normalized((t_fvec3){cam->normalize.z, 0, -cam->normalize.x}));
	cam->up = dmul((cam->len_opp / cam->ratio),
			normalized(cross(normalized(cam->normalize), cam->right)));
}

t_fvec3	get_ray_direction(t_camera *cam, double x, double y, t_w *w)
{
	double	coord_x;
	double	coord_y;

	coord_x = (x - (w->size_x / 2)) / w->size_x;
	coord_y = (y - (w->size_y / 2)) / w->size_y;
	return (sum(sum(dmul(coord_x, cam->right),
				dmul(-coord_y, cam->up)), cam->normalize));
}
