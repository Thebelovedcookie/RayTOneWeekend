/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_scene_parse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonouelg <sonouelg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:08:56 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/25 13:10:50 by sonouelg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_space(char *tmp, int bool, char *str, t_scene *scene)
{
	if (tmp[0] != ',' && bool == 1)
		error(tmp, scene, str);
	if (bool == 1 && (!(tmp[1] >= '0' && tmp[1] <= '9') && tmp[1] != '-'))
		error(tmp, scene, str);
	if (tmp[0] != ' ' && bool == 0)
		error(tmp, scene, str);
	return ;
}

t_fvec3	create_fvec3(char **tmp, t_scene *scene, char *str)
{
	t_fvec3	result;

	result.x = ft_strtod(*tmp, tmp);
	check_space(*tmp, 1, str, scene);
	result.y = ft_strtod(*tmp, tmp);
	check_space(*tmp, 1, str, scene);
	result.z = ft_strtod(*tmp, tmp);
	return (result);
}

t_vec3	create_vec3(char **tmp, t_scene *scene, char *str)
{
	t_vec3	result;

	result.r = (int)ft_strtod(*tmp, tmp);
	check_space(*tmp, 1, str, scene);
	result.g = (int)ft_strtod(*tmp, tmp);
	check_space(*tmp, 1, str, scene);
	result.b = (int)ft_strtod(*tmp, tmp);
	return (result);
}

void	check_plane_value(t_plane *p, t_scene *scene, t_vec3 c, char *str)
{
	if ((p->dir.x < -1.0 || p->dir.x > 1.0) || (p->dir.y < -1.0
			|| p->dir.y > 1.0) || (p->dir.z < -1.0 || p->dir.z > 1.0))
		error("Plane : normalize", scene, str);
	if ((c.b < 0 || c.b > 255) || (c.g < 0 || c.g > 255)
		|| (c.r < 0 || c.r > 255))
		error("Plane : color", scene, str);
	p->color.x = (double)c.r / 255;
	p->color.y = (double)c.g / 255;
	p->color.z = (double)c.b / 255;
}

void	check_cyl_val(t_cylindre *cy, t_scene *scene, t_vec3 c, char *str)
{
	if ((cy->axe.x < -1.0 || cy->axe.x > 1.0) || (cy->axe.y < -1.0
			|| cy->axe.y > 1.0) || (cy->axe.z < -1.0 || cy->axe.z > 1.0))
		error("Cylinder : normalize", scene, str);
	if ((c.b < 0 || c.b > 255) || (c.g < 0 || c.g > 255)
		|| (c.r < 0 || c.r > 255))
		error("Cylinder : color", scene, str);
	cy->color.x = (double)c.r / 255;
	cy->color.y = (double)c.g / 255;
	cy->color.z = (double)c.b / 255;
}
