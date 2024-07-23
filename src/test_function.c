/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:00:07 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/23 12:07:01 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_scene(t_scene *scene)
{
	t_sphere	*sphere_tmp;
	t_plane		*plane_tmp;
	t_cylindre	*cylindre_tmp;

	sphere_tmp = *(scene->tab_sp);
	plane_tmp = *(scene->tab_pl);
	cylindre_tmp = *(scene->tab_cy);
	printf("----------Ambient :----------\n"
		" ratio		: %.2f\n"
		" color		: r: %f, g: %f, b: %f\n",
		scene->ambi.ratio,
		scene->ambi.color.x,
		scene->ambi.color.y,
		scene->ambi.color.z);
	printf("----------Camera :----------\n"
		" viewpoint	: x : %.2f, y: %.2f, z: %.2f\n"
		" normalize 	: x: %.2f, y: %.2f, z: %.2f\n"
		" fov		: %f\n",
		scene->cam.view_point.x,
		scene->cam.view_point.y,
		scene->cam.view_point.z,
		scene->cam.normalize.x,
		scene->cam.normalize.y,
		scene->cam.normalize.z,
		scene->cam.fov);
	printf("----------Light :----------\n"
		" light_point	: x: %.2f, y: %.2f, z: %.2f\n"
		" brightness	: %.2f\n",
		scene->light.light_point.x,
		scene->light.light_point.y,
		scene->light.light_point.z,
		scene->light.brightness);
	while (sphere_tmp)
	{
		printf("----------Sphere :----------\n"
			" center		: x: %.2f, y: %.2f, z: %.2f\n"
			" diam		: %.2f\n"
			" color		: r: %f, g: %f, b: %f\n",
			sphere_tmp->center.x,
			sphere_tmp->center.y,
			sphere_tmp->center.z,
			sphere_tmp->diameter,
			sphere_tmp->color.x,
			sphere_tmp->color.y,
			sphere_tmp->color.z);
		sphere_tmp = sphere_tmp->next;
	}
	while (cylindre_tmp)
	{
		printf("----------Cylindre :----------\n"
			" center		: x: %.2f, y: %.2f, z: %.2f \n"
			" normalize	: x: %.2f, y: %.2f, z: %.2f, \n"
			" diam		: %.2f\n"
			" height		: %.2f\n"
			" color		: r: %f, g: %f, b: %f \n",
			cylindre_tmp->center.x,
			cylindre_tmp->center.y,
			cylindre_tmp->center.z,
			cylindre_tmp->axe.x,
			cylindre_tmp->axe.y,
			cylindre_tmp->axe.z,
			cylindre_tmp->diameter,
			cylindre_tmp->height,
			cylindre_tmp->color.x,
			cylindre_tmp->color.y,
			cylindre_tmp->color.z);
		cylindre_tmp = cylindre_tmp->next;
	}
	while (plane_tmp)
	{
		printf("----------Plane :----------\n"
			" point		: x: %.2f, y: %.2f, z: %.2f\n"
			" normalize	: x: %.2f y: %.2f, z: %.2f\n"
			" color 		: r: %f, g: %f, b: %f \n",
			plane_tmp->point.x,
			plane_tmp->point.y,
			plane_tmp->point.z,
			plane_tmp->normalize.x,
			plane_tmp->normalize.y,
			plane_tmp->normalize.z,
			plane_tmp->color.x,
			plane_tmp->color.y,
			plane_tmp->color.z);
		plane_tmp = plane_tmp->next;
	}
}

void	print_vec3(t_fvec3 a, char *name)
{
	printf("%s : x = %f \t y = %f \t z = %f \n", name, a.x, a.y, a.z);
}