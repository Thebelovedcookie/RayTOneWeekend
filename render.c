/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 21:01:16 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/12 16:02:48 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	create_trgb(t_fvec3 color)
{
	t_vec3	color_int;

	color_int.red = color.x * 255;
	color_int.green = color.y * 255;
	color_int.blue = color.z * 255;
	return (color_int.red << 16 | color_int.green << 8
		| color_int.blue);
}

void	my_mlx_pixel_put(t_window *window, int x, int y, int color)
{
	char	*dst;

	dst = window->img.addr + (y * window->img.line_length
			+ x * (window->img.bbp / 8));
	*(unsigned int *)dst = color;
}

void	aspect_ratio(t_window *window)
{
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

	t_fvec3	tmp1;
	t_fvec3	tmp2;

	tmp1 = minus_vec3(window->scene->cam.view_point, (t_fvec3){0, 0, window->scene->cam.focal_length});
	tmp2 = minus_vec3(tmp1, divide_vec3(window->scene->cam.viewport_u, 2.0));
	window->scene->cam.viewport_upper_left = minus_vec3(tmp2, divide_vec3(window->scene->cam.viewport_v, 2.0));
	window->scene->cam.pixel00_loc = sum_vec3(window->scene->cam.viewport_upper_left,
	double_x_vec3(0.5, sum_vec3(window->scene->cam.pixel_delta_u, window->scene->cam.pixel_delta_v)));
}

double	hit_sphere(t_window *window, t_sphere *sphere)
{
	t_fvec3	vector_origin_center;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	vector_origin_center = minus_vec3(sphere->center, window->scene->cam.view_point);
	a = length_squared(window->ray.ray_direction);
	b = dot_product(window->ray.ray_direction, vector_origin_center);
	c = length_squared(vector_origin_center) - ((sphere->diameter / 2.0) * (sphere->diameter / 2.0));
	discriminant = b * b - (a * c);
	if (discriminant < 0.0)
		return (-1.0);
	return (b - sqrt(discriminant) / a);
}

double	hit_light(t_window *window, t_sphere *sphere)
{
	t_fvec3	vector_origin_center;
	double	a;
	double	b;
	double	c;
	double	discriminant;

	vector_origin_center = minus_vec3(sphere->center, window->scene->light.light_point);
	a = length_squared(window->scene->light.ray_direction);
	b = dot_product(window->scene->light.ray_direction, vector_origin_center);
	c = length_squared(vector_origin_center) - ((sphere->diameter / 2.0) * (sphere->diameter / 2.0));
	discriminant = b * b - (a * c);
	if (discriminant < 0.0)
		return (-1.0);
	return (b - sqrt(discriminant) / a);
}

t_fvec3	at(double t, t_window *window)
{
	return (sum_vec3(window->scene->cam.view_point, double_x_vec3(t, window->ray.ray_direction)));
}

t_fvec3	get_color(t_window *window)
{
	t_fvec3		vector;
	t_sphere	*sphere;
	double		t;
	double		tt;
	t_fvec3		vec_ratio;
	double		ratio;

	sphere = *(window->scene->tab_sp);
	while (sphere)
	{
		t = hit_sphere(window, sphere);
		if (t >= 0.0)
		{
			vector = unit_vector(minus_vec3(at(t, window), sphere->center));
			vector = double_x_vec3(0.5, (t_fvec3){vector.x + 1, vector.y + 1, vector.z + 1});
			vec_ratio = vector_cross_vec3(at(t, window), vector);
			ratio = length(vec_ratio);
			tt = hit_light(window, sphere);
			vector = unit_vector(minus_vec3(at(tt, window), sphere->center));
			vec_ratio = vector_cross_vec3(at(t, window), vector);
			ratio = ratio * length(vec_ratio);
			return (double_x_vec3(window->scene->light.brightness ,double_x_vec3(1.0 - ratio, sphere->color)));
		}
		sphere = sphere->next;
	}
	return ((t_fvec3){0, 0, 0});
}

int	render(void *param)
{
	t_window	*window;
	int			x;
	int			y;
	t_fvec3		pixel_center;
	t_fvec3		color;

	x = 0;
	y = 0;
	window = (t_window *)param;
	aspect_ratio(window);
	while (y < window->ratio.image_height)
	{
		x = 0;
		while (x < window->size_x)
		{
			pixel_center = sum_vec3(sum_vec3(window->scene->cam.pixel00_loc,
						double_x_vec3(x, window->scene->cam.pixel_delta_u)),
					double_x_vec3(y, window->scene->cam.pixel_delta_v));
			window->ray.ray_direction = minus_vec3(pixel_center, window->scene->cam.view_point);
			window->scene->light.ray_direction = minus_vec3(pixel_center, window->scene->light.light_point);
			color = get_color(window);
			my_mlx_pixel_put(window, x, y, create_trgb(color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, window->img.img_ptr, 0, 0);
	return (0);
}
