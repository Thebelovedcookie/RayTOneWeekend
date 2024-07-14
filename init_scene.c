/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:27:37 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/12 20:03:49 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	*create_scene(void)
{
	t_scene	*scene;

	scene = malloc(1 * sizeof(t_scene));
	if (!scene)
		ex_malloc_fail(scene);
	scene->ambi.color = (t_fvec3){0, 0, 0};
	scene->ambi.ratio = 0.0;
	scene->cam.view_point = (t_fvec3){0.0, 0.0, 0.0};
	scene->cam.normalize = (t_fvec3){0.0, 0.0, 0.0};
	scene->cam.fov = 0;
	scene->light.light_point = (t_fvec3){0.0, 0.0, 0.0};
	scene->light.brightness = 0.0;
	scene->tab_sp = malloc(1 * sizeof(t_sphere *));
	if (!scene->tab_sp)
		ex_malloc_fail(scene);
	*(scene->tab_sp) = NULL;
	scene->tab_pl = malloc(1 * sizeof(t_plane *));
	if (!scene->tab_pl)
		ex_malloc_fail(scene);
	*(scene->tab_pl) = NULL;
	scene->tab_cy = malloc(1 * sizeof(t_cylindre *));
	if (!scene->tab_cy)
		ex_malloc_fail(scene);
	*(scene->tab_cy) = NULL;
	scene->nb_object = 0;
	return (scene);
}

t_sphere	*new_sphere(t_scene *scene)
{
	t_sphere	*new;

	new = malloc (1 * sizeof(t_sphere));
	if (!new)
		ex_malloc_fail(scene);
	new->center = (t_fvec3){0.0, 0.0, 0.0};
	new->color = (t_fvec3){0, 0, 0};
	new->diameter = 0.0;
	new->next = NULL;
	return (new);
}

t_plane	*new_plane(t_scene *scene)
{
	t_plane	*new;

	new = malloc (1 * sizeof(t_plane));
	if (!new)
		ex_malloc_fail(scene);
	new->normalize = (t_fvec3){0.0, 0.0, 0.0};
	new->color = (t_fvec3){0, 0, 0};
	new->point = (t_fvec3){0.0, 0.0, 0.0};
	new->next = NULL;
	return (new);
}

t_cylindre	*new_cylindre(t_scene *scene)
{
	t_cylindre	*new;

	new = malloc (1 * sizeof(t_cylindre));
	if (!new)
		ex_malloc_fail(scene);
	new->normalize = (t_fvec3){0.0, 0.0, 0.0};
	new->color = (t_fvec3){0, 0, 0};
	new->height = 0.0;
	new->center = (t_fvec3){0.0, 0.0, 0.0};
	new->diameter = 0.0;
	new->next = NULL;
	return (new);
}
