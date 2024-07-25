/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonouelg <sonouelg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:38:41 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/25 12:48:56 by sonouelg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_tab_sp(t_sphere ***sphere)
{
	t_sphere	*tmp;

	if (**sphere)
	{
		tmp = (**sphere);
		while (tmp)
		{
			**sphere = (**sphere)->next;
			free(tmp);
			tmp = **sphere;
		}
		free(*sphere);
		*sphere = NULL;
	}
}

void	free_tab_pl(t_plane ***plane)
{
	t_plane	*tmp;

	if (**plane)
	{
		tmp = (**plane);
		while (tmp)
		{
			**plane = (**plane)->next;
			free(tmp);
			tmp = **plane;
		}
		free(*plane);
		*plane = NULL;
	}
}

void	free_tab_inter(t_w *w)
{
	int	i;

	i = 0;
	while (i < w->scene->nb_object)
	{
		free(w->tab_inter[i]);
		i++;
	}
	free(w->tab_inter);
}
