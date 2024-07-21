/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 21:01:16 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/21 22:17:24 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	create_trgb(t_fvec3 color)
{
	t_vec3	color_int;

	color_int.red = color.x * 255;
	if (color_int.red > 255)
		color_int.red = 255;
	color_int.green = color.y * 255;
	if (color_int.green > 255)
		color_int.green = 255;
	color_int.blue = color.z * 255;
	if (color_int.blue > 255)
		color_int.blue = 255;
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

t_fvec3	at(double t, t_window *window)
{
	return (sum_vec3(window->scene->cam.view_point,
			double_x_vec3(t, window->ray.ray_direction)));
}

void	add_to_tab(t_window *window, int index, int type_obj, double t)
{
	window->tab_inter[index - 1][0] = type_obj;
	window->tab_inter[index - 1][1] = t;
	window->tab_inter[index - 1][2] = index;
}

int	hit(t_window *window)
{
	int		i;

	i = 0;
	window->hit.lowest_t = INT_MAX;
	while (i < window->scene->nb_object)
	{
		if (window->tab_inter[i][1] > 0 && window->tab_inter[i][1] < window->hit.lowest_t)
		{
			window->hit.type_objet = window->tab_inter[i][0];
			window->hit.lowest_t = window->tab_inter[i][1];
			window->hit.nb_objet = window->tab_inter[i][2];
		}
		i++;
	}
	if (window->hit.lowest_t == INT_MAX)
	{
		window->hit.lowest_t = 0;
		return (0);
	}
	return (1);
}

t_fvec3	get_color(t_window *window)
{
	if (hit(window))
	{
		if (window->hit.type_objet == 1)
			return (sphere_hitted(window));
		if (window->hit.type_objet == 2)
			return (plane_hitted(window));
		if (window->hit.type_objet == 3)
			return (cylinder_hitted(window));
	}
	return (double_x_vec3(window->scene->ambi.ratio,
			window->scene->ambi.color));
}

void	intersect_function(t_window *window)
{
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylindre	*cylind;
	double		t;

	init_tab(window);
	sphere = *(window->scene->tab_sp);
	while (sphere)
	{
		t = hit_sphere(window, sphere);
		if (t > 0.0)
		{
			add_to_tab(window, sphere->n_object, 1, t);
		}
		sphere = sphere->next;
	}
	plane = *(window->scene->tab_pl);
	while (plane)
	{
		t = hit_plane(window, plane);
		if (t > 0.0)
			add_to_tab(window, plane->n_object, 2, t);
		plane = plane->next;
	}
	cylind = *(window->scene->tab_cy);
	while (cylind)
	{
		t = hit_cylinder(window, cylind);
		if (t > 0.0)
		{
			add_to_tab(window, cylind->n_object, 3, t);
		}
		cylind = cylind->next;
	}
}

// int	render(void *param)
// {
// 	t_window	*window;
// 	int			x;
// 	int			y;
// 	t_fvec3		pixel_center;
// 	t_fvec3		color;

// 	x = 0;
// 	y = 0;
// 	window = (t_window *)param;
// 	aspect_ratio(window);
// 	while (y < window->ratio.image_height)
// 	{
// 		x = 0;
// 		while (x < window->size_x)
// 		{
// 			pixel_center = sum_vec3(sum_vec3(window->scene->cam.pixel00_loc,
// 						double_x_vec3(x, window->scene->cam.pixel_delta_u)),
// 					double_x_vec3(y, window->scene->cam.pixel_delta_v));
// 			window->ray.ray_direction = minus_vec3(pixel_center, window->scene->cam.view_point);
// 			window->scene->light.ray_direction = minus_vec3(pixel_center, window->scene->light.light_point);
// 			intersect_function(window);
// 			color = get_color(window);
// 			my_mlx_pixel_put(window, x, y, create_trgb(color));
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, window->img.img_ptr, 0, 0);
// 	return (0);
// }

int	render(void *param)
{
	t_window	*window;
	int			x;
	int			y;
	double		a;
	double		b;
	t_fvec3		color;

	x = 0;
	y = 0;
	window = (t_window *)param;
	calc_base(window, &window->scene->cam);
	while (y < window->size_y)
	{
		x = 0;
		while (x < window->size_x)
		{
			a = (double)x / (window->size_x - 1);
			b = (double)y / (window->size_y - 1);
			window->ray.ray_direction = get_ray_direction(&window->scene->cam, a, b);
			intersect_function(window);
			color = get_color(window);
			my_mlx_pixel_put(window, x, y, create_trgb(color));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(window->mlx_ptr, window->win_ptr, window->img.img_ptr, 0, 0);
	return (0);
}