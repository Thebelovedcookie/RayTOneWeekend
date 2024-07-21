/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:49:14 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/20 17:07:15 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	create_window(t_scene *scene, t_window *window)
{
	window->mlx_ptr = mlx_init();
	if (!window->mlx_ptr)
		error_window(NULL, scene);
	mlx_get_screen_size(window->mlx_ptr, &window->size_x, &window->size_y);
	printf("x = %d y = %d\n", window->size_x, window->size_y);
	window->size_x /= 2;
	window->size_y = window->size_x;
	window->win_ptr = mlx_new_window(window->mlx_ptr, window->size_x,
			window->size_y, "my_window");
	if (!window->win_ptr)
		error_window(window->mlx_ptr, scene);
	window->img.img_ptr = mlx_new_image(window->mlx_ptr, window->size_x,
			window->size_y);
	window->img.addr = mlx_get_data_addr(window->img.img_ptr, &window->img.bbp,
			&window->img.line_length, &window->img.endian);
	mlx_hook(window->win_ptr, 2, 1L << 0, &close_via_escape, (void *)window);
	mlx_hook(window->win_ptr, 17, 1L << 3, &close_via_cross, (void *)window);
	mlx_loop_hook(window->mlx_ptr, &render, window);
	mlx_loop(window->mlx_ptr);
}

int	close_via_cross(void *param)
{
	t_window	*window;

	window = (t_window *)param;
	mlx_clear_window(window->mlx_ptr, window->win_ptr);
	mlx_destroy_window(window->mlx_ptr, window->win_ptr);
	mlx_destroy_display(window->mlx_ptr);
	free(window->mlx_ptr);
	free_scene(window->scene);
	exit(EXIT_SUCCESS);
	return (0);
}

int	close_via_escape(int keycode, void *param)
{
	t_window	*window;

	window = (t_window *)param;
	if (keycode == 65307)
	{
		mlx_clear_window(window->mlx_ptr, window->win_ptr);
		mlx_destroy_window(window->mlx_ptr, window->win_ptr);
		mlx_destroy_display(window->mlx_ptr);
		free(window->mlx_ptr);
		free_scene(window->scene);
		exit(EXIT_SUCCESS);
	}
	return (0);
}
