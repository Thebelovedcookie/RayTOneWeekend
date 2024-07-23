/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:38:41 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/06/22 21:19:24 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_scene(t_scene *scene)
{
	if (scene)
	{
		if (scene->tab_cy)
			free_tab_cy(&(scene->tab_cy));
		if (scene->tab_pl)
			free_tab_pl(&(scene->tab_pl));
		if (scene->tab_sp)
			free_tab_sp(&(scene->tab_sp));
		free(scene);
		scene = NULL;
	}
}

void	free_tab_cy(t_cylindre ***cylindre)
{
	t_cylindre	*tmp;

	if (**cylindre)
	{
		tmp = (**cylindre);
		while (tmp)
		{
			**cylindre = (**cylindre)->next;
			free(tmp);
			tmp = **cylindre;
		}
		free(*cylindre);
		*cylindre = NULL;
	}
}

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
