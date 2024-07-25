/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonouelg <sonouelg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:37:45 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/25 13:13:08 by sonouelg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error(char *error, t_scene *scene, char *str)
{
	ft_fprintf(2, "Error\nbad input format with %s\n", error);
	while (str)
	{
		free(str);
		str = get_next_line(scene->fd);
	}
	if (close(scene->fd) == -1)
		ft_fprintf(2, "i can't close\n");
	free_scene(&scene);
	exit(EXIT_FAILURE);
}

void	ex_malloc_fail(t_scene *scene)
{
	ft_fprintf(2, "Malloc has failed\n");
	if (scene)
		free_scene(&scene);
	exit(EXIT_FAILURE);
}

void	error_w(void *mlx_ptr, t_scene *scene)
{
	if (!mlx_ptr)
		ft_fprintf(2, "Failed to initiat mlx_ptr\n");
	else
	{
		ft_fprintf(2, "Failed to open a new_w\n");
		free(mlx_ptr);
	}
	if (scene)
		free_scene(&scene);
	exit(EXIT_FAILURE);
}
