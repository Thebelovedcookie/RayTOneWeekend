/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:37:45 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/06/22 20:48:13 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error(char *error, t_scene *scene)
{
	ft_fprintf(2, "Error: bad input format with %s\n", error);
	free_scene(scene);
	exit(EXIT_FAILURE);
}

void	ex_malloc_fail(t_scene *scene)
{
	ft_fprintf(2, "Malloc has failed\n");
	if (scene)
		free_scene(scene);
	exit(EXIT_FAILURE);
}

void	error_window(void *mlx_ptr, t_scene *scene)
{
	if (!mlx_ptr)
		ft_fprintf(2, "Failed to initiat mlx_ptr\n");
	else
	{
		ft_fprintf(2, "Failed to open a new_window\n");
		free(mlx_ptr);
	}
	if (scene)
		free_scene(scene);
	exit(EXIT_FAILURE);
}
