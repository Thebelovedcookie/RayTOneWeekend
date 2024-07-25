/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:49:14 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/23 11:01:23 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_w(t_scene *scene, t_w *w)
{
	w->mlx_ptr = mlx_init();
	if (!w->mlx_ptr)
		error_w(NULL, scene);
	mlx_get_screen_size(w->mlx_ptr, &w->size_x, &w->size_y);
	w->size_x /= 2;
	w->size_y = w->size_x;
	w->win_ptr = mlx_new_window(w->mlx_ptr, w->size_x,
			w->size_y, "minirt");
	if (!w->win_ptr)
		error_w(w->mlx_ptr, scene);
	w->img.img_ptr = mlx_new_image(w->mlx_ptr, w->size_x,
			w->size_y);
	w->img.addr = mlx_get_data_addr(w->img.img_ptr, &w->img.bbp,
			&w->img.line_length, &w->img.endian);
	mlx_hook(w->win_ptr, 2, 1L << 0, &close_via_escape, (void *)w);
	mlx_hook(w->win_ptr, 17, 1L << 3, &close_via_cross, (void *)w);
	mlx_loop_hook(w->mlx_ptr, &render, w);
	mlx_loop(w->mlx_ptr);
}

int	close_via_cross(void *param)
{
	t_w	*w;

	w = (t_w *)param;
	mlx_destroy_image(w->mlx_ptr, w->img.img_ptr);
	mlx_clear_window(w->mlx_ptr, w->win_ptr);
	mlx_destroy_window(w->mlx_ptr, w->win_ptr);
	mlx_destroy_display(w->mlx_ptr);
	free(w->mlx_ptr);
	free_all(w);
	exit(EXIT_SUCCESS);
	return (0);
}

int	close_via_escape(int keycode, void *param)
{
	t_w	*w;

	w = (t_w *)param;
	if (keycode == 65307)
	{
		mlx_destroy_image(w->mlx_ptr, w->img.img_ptr);
		mlx_clear_window(w->mlx_ptr, w->win_ptr);
		mlx_destroy_window(w->mlx_ptr, w->win_ptr);
		mlx_destroy_display(w->mlx_ptr);
		free(w->mlx_ptr);
		free_all(w);
		exit(EXIT_SUCCESS);
	}
	return (0);
}
