/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:51:31 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/22 17:07:39 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	calc_base(t_window *window, t_camera *cam)
{
	t_fvec3	vise;

	vise = sum_vec3(cam->view_point, cam->normalize);
	cam->theta = (cam->fov * M_PI) / 180;
	cam->h = tan(cam->theta / 2);
	cam->viewport_height = 2.0 * cam->h;
	cam->viewport_width = (window->size_x / window->size_y) * cam->viewport_height;
	cam->w = normalized(sub_vec(cam->view_point, vise));
	cam->u = normalized(cross_prod((t_fvec3){0, 1, 0}, cam->w));
	cam->v = cross_prod(cam->w, cam->u);
	cam->horiz = double_x_vec3(cam->viewport_width, cam->u);
	cam->verti = double_x_vec3(cam->viewport_height, cam->v);
	cam->lower_left_corner = sub_vec(sub_vec(sub_vec(cam->view_point, divide_vec3(cam->horiz, 2.0)), divide_vec3(cam->verti, 2.0)), cam->w);
}

t_fvec3	get_ray_direction(t_camera *cam, double x, double y)
{
	return (sub_vec(sum_vec3(sum_vec3(cam->lower_left_corner,
					double_x_vec3(x, cam->horiz)),
				double_x_vec3((1.0 - y), cam->verti)), cam->view_point));
}
