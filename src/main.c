/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonouelg <sonouelg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 21:13:13 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/25 13:30:03 by sonouelg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	**create_tab(t_w *w)
{
	double	**tab;
	int		i;

	i = 0;
	tab = malloc(w->scene->nb_object * sizeof(double *));
	if (!tab)
		printf("malloc failed\n");
	while (i < w->scene->nb_object)
	{
		tab[i] = malloc(3 * sizeof(double));
		if (!tab[i])
			printf("malloc failed here\n");
		i++;
	}
	return (tab);
}

void	init_tab(t_w *w)
{
	int	i;
	int	j;

	i = 0;
	while (i < w->scene->nb_object)
	{
		j = 0;
		while (j < 3)
		{
			w->tab_inter[i][j] = 0.0;
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	int			fd;
	t_w			w;

	if (argc != 2)
	{
		ft_fprintf(2, "Wrong arg number.\n");
		return (1);
	}
	fd = open_my_file(argv[1]);
	w.scene = read_my_file(fd);
	if (close(fd) == -1)
		ft_fprintf(2, "i can't close\n");
	w.tab_inter = create_tab(&w);
	init_tab(&w);
	create_w(w.scene, &w);
	free_all(&w);
	return (0);
}
