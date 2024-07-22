/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 21:13:13 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/22 10:57:47 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	**create_tab(t_window *window)
{
	double	**tab;
	int		i;

	i = 0;
	tab = malloc(window->scene->nb_object * sizeof(double *));
	if (!tab)
		printf("malloc failed\n");
	while (i < window->scene->nb_object)
	{
		tab[i] = malloc(3 * sizeof(double));
		if (!tab[i])
			printf("malloc failed here\n");
		i++;
	}
	return (tab);
}

void	init_tab(t_window *window)
{
	int	i;
	int	j;

	i = 0;
	while (i < window->scene->nb_object)
	{
		j = 0;
		while (j < 3)
		{
			window->tab_inter[i][j] = 0.0;
			j++;
		}
		i++;
	}
}

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
	window.tab_inter = create_tab(&window);
	init_tab(&window);
	print_scene(window.scene);
	create_window(window.scene, &window);
	free_scene(window.scene);
	if (close(fd) == -1)
		ft_fprintf(2, "i can't close\n");
	return (0);
}
