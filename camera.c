/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:51:31 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/20 17:03:50 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// void	aspect_ratio(t_window *window)
// {
// 	t_fvec3	tmp1;
// 	t_fvec3	tmp2;

// 	window->ratio.aspect_ratio = 16.0 / 9.0;
// 	window->ratio.image_height = (double)window->size_x / window->ratio.aspect_ratio;
// 	if (window->ratio.image_height < 1)
// 		window->ratio.image_height = 1;
// 	//camera
// 	window->scene->cam.focal_length = 1.0;
// 	window->ratio.viewport_height = 2.0;
// 	window->ratio.viewport_width = window->ratio.viewport_height
// 		* ((double)window->size_x / window->ratio.image_height);
// 	//vector
// 	window->scene->cam.viewport_u = (t_fvec3){window->ratio.viewport_width, 0, 0};
// 	window->scene->cam.viewport_v = (t_fvec3){0, -window->ratio.viewport_height, 0};
// 	//delta calc
// 	window->scene->cam.pixel_delta_u = divide_vec3(window->scene->cam.viewport_u, (double)window->size_x);
// 	window->scene->cam.pixel_delta_v = divide_vec3(window->scene->cam.viewport_v, window->ratio.image_height);
// 	//calc upper left pixel
// 	tmp1 = minus_vec3(window->scene->cam.view_point,
// 			(t_fvec3){0, 0, window->scene->cam.focal_length});
// 	tmp2 = minus_vec3(tmp1, divide_vec3(window->scene->cam.viewport_u, 2.0));
// 	window->scene->cam.viewport_upper_left = minus_vec3(tmp2,
// 			divide_vec3(window->scene->cam.viewport_v, 2.0));
// 	window->scene->cam.pixel00_loc = sum_vec3(window->scene->cam.viewport_upper_left,
// 	double_x_vec3(0.5, sum_vec3(window->scene->cam.pixel_delta_u, window->scene->cam.pixel_delta_v)));
// }


void	calc_base(t_window *window, t_camera *cam)
{
	t_fvec3	vise;

	vise = sum_vec3(cam->view_point, cam->normalize);
	cam->theta = (cam->fov * M_PI) / 180;
	cam->h = tan(cam->theta / 2);
	cam->viewport_height = 2.0 * cam->h;
	cam->viewport_width = (window->size_x / window->size_y) * cam->viewport_height;
	cam->w = unit_vector(minus_vec3(cam->view_point, vise));
	cam->u = unit_vector(vector_cross_vec3((t_fvec3){0, 1, 0}, cam->w));
	cam->v = vector_cross_vec3(cam->w, cam->u);
	cam->horiz = double_x_vec3(cam->viewport_width, cam->u);
	cam->verti = double_x_vec3(cam->viewport_height, cam->v);
	cam->lower_left_corner = minus_vec3(minus_vec3(minus_vec3(cam->view_point, divide_vec3(cam->horiz, 2.0)), divide_vec3(cam->verti, 2.0)), cam->w);
}

t_fvec3	get_ray_direction(t_camera *cam, double x, double y)
{
	return (minus_vec3(sum_vec3(sum_vec3(cam->lower_left_corner,
					double_x_vec3(x, cam->horiz)),
				double_x_vec3((1.0 - y), cam->verti)), cam->view_point));
}
