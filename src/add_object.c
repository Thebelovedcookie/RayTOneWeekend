/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 13:05:56 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/25 11:58:04 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_sphere(char *str, t_scene *scene)
{
	t_sphere	*tmp;

	if (!(*(scene->tab_sp)))
	{
		*(scene->tab_sp) = new_sphere(scene);
		tmp = *(scene->tab_sp);
	}
	else
	{
		tmp = *(scene->tab_sp);
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_sphere(scene);
		tmp = tmp->next;
	}
	fill_sphere(str, tmp, scene);
}

void	add_plane(char *str, t_scene *scene)
{
	t_plane	*tmp;

	tmp = *(scene->tab_pl);
	if (!(*(scene->tab_pl)))
	{
		*(scene->tab_pl) = new_plane(scene);
		tmp = *(scene->tab_pl);
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_plane(scene);
		tmp = tmp->next;
	}
	fill_plane(str, tmp, scene);
}

void	add_cylinder(char *str, t_scene *scene)
{
	t_cylindre	*tmp;

	tmp = *(scene->tab_cy);
	if (!(*(scene->tab_cy)))
	{
		*(scene->tab_cy) = new_cylindre(scene);
		tmp = *(scene->tab_cy);
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_cylindre(scene);
		tmp = tmp->next;
	}
	fill_cylindre(str, tmp, scene);
}
