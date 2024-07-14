/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:51:31 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/12 21:53:17 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	aspect_ratio(t_window *window)
{
	t_fvec3	tmp1;
	t_fvec3	tmp2;

	window->ratio.aspect_ratio = 16.0 / 9.0;
	window->ratio.image_height = (double)window->size_x / window->ratio.aspect_ratio;
	if (window->ratio.image_height < 1)
		window->ratio.image_height = 1;
	//camera
	window->scene->cam.focal_length = 1.0;
	window->ratio.viewport_height = 2.0;
	window->ratio.viewport_width = window->ratio.viewport_height
		* ((double)window->size_x / window->ratio.image_height);
	//vector
	window->scene->cam.viewport_u = (t_fvec3){window->ratio.viewport_width, 0, 0};
	window->scene->cam.viewport_v = (t_fvec3){0, -window->ratio.viewport_height, 0};
	//delta calc
	window->scene->cam.pixel_delta_u = divide_vec3(window->scene->cam.viewport_u, (double)window->size_x);
	window->scene->cam.pixel_delta_v = divide_vec3(window->scene->cam.viewport_v, window->ratio.image_height);
	//calc upper left pixel
	tmp1 = minus_vec3(window->scene->cam.view_point,
			(t_fvec3){0, 0, window->scene->cam.focal_length});
	tmp2 = minus_vec3(tmp1, divide_vec3(window->scene->cam.viewport_u, 2.0));
	window->scene->cam.viewport_upper_left = minus_vec3(tmp2,
			divide_vec3(window->scene->cam.viewport_v, 2.0));
	window->scene->cam.pixel00_loc = sum_vec3(window->scene->cam.viewport_upper_left,
	double_x_vec3(0.5, sum_vec3(window->scene->cam.pixel_delta_u, window->scene->cam.pixel_delta_v)));
}

