/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:51:31 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/24 00:02:01 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	calc_base(t_w *w, t_camera *cam)
// {
// 	t_fvec3	vise;

// 	vise = sum(cam->view_point, cam->normalize);
// 	cam->theta = (cam->fov * M_PI) / 180;
// 	cam->h = tan(cam->theta / 2);
// 	cam->viewport_height = 2.0 * cam->h;
// 	cam->viewport_width = (w->size_x / w->size_y)
// 		* cam->viewport_height;
// 	cam->w = normalized(sub(cam->view_point, vise));
// 	cam->u = normalized(cross((t_fvec3){0, 1, 0}, cam->w));
// 	cam->v = cross(cam->w, cam->u);
// 	cam->horiz = dmul(cam->viewport_width, cam->u);
// 	cam->verti = dmul(cam->viewport_height, cam->v);
// 	cam->lower_left_corner = sub(sub(sub(cam->view_point,
// 					dive(cam->horiz, 2.0)), dive(cam->verti, 2.0)), cam->w);
// }

void	camera(t_w *w, t_camera *cam)
{
	cam->ratio = w->size_x / w->size_y;
	cam->angle = (cam->fov * M_PI) / 180;
	cam->len_opp = tan(cam->angle / 2);
	cam->right = dmul(cam->len_opp, normalized((t_fvec3){cam->normalize.z, 0, -cam->normalize.x}));
	cam->up = dmul((cam->len_opp / cam->ratio), normalized(cross(normalized(cam->normalize), cam->right)));
}

t_fvec3	get_ray_direction(t_camera *cam, double x, double y, t_w *w)
{
	double	coord_x;
	double	coord_y;

	coord_x = (x - (w->size_x / 2)) / w->size_x;
	coord_y = (y - (w->size_y / 2)) / w->size_y;
	return (sum(sum(dmul(coord_x, cam->right), dmul(-coord_y, cam->up)), cam->normalize));
}
