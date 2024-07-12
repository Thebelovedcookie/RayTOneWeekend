/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 21:13:13 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/06/22 20:50:33 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	int			fd;
	t_window	window;

	if (argc != 2)
	{
		ft_fprintf(2, "Wrong arg number.\n");
		return (1);
	}
	fd = open_my_file(argv[1]);
	window.scene = read_my_file(fd);
	print_scene(window.scene);
	create_window(window.scene, &window);
	free_scene(window.scene);
	if (close(fd) == -1)
		ft_fprintf(2, "i can't close\n");
	return (0);
}
