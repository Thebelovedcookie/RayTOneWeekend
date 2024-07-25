/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_scene_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonouelg <sonouelg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 20:11:40 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/25 13:11:37 by sonouelg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	fill_cylindre(char *str, t_cylindre *cy, t_scene *scene)
{
	int		i;
	char	*t;
	t_vec3	c;

	i = 0;
	while (str[i] && (!(str[i] >= '0' && str[i] <= '9') && str[i] != '-'))
		i++;
	if (str[i] == '\0')
		error("cylindre : no input", scene, str);
	t = &str[i];
	cy->center = create_fvec3(&t, scene, str);
	check_space(t, 0, str, scene);
	cy->axe = create_fvec3(&t, scene, str);
	check_space(t, 0, str, scene);
	cy->diameter = ft_strtod(t, &t);
	check_space(t, 0, str, scene);
	cy->height = ft_strtod(t, &t);
	check_space(t, 0, str, scene);
	c = create_vec3(&t, scene, str);
	check_cyl_val(cy, scene, c, str);
	scene->nb_object += 1;
	cy->n_object = scene->nb_object;
}

void	fill_plane(char *str, t_plane *p, t_scene *scene)
{
	int		i;
	char	*tmp;
	t_vec3	c;

	i = 0;
	while (str[i] && (!(str[i] >= '0' && str[i] <= '9') && str[i] != '-'))
		i++;
	if (str[i] == '\0')
		error("Plane: no input", scene, str);
	tmp = &str[i];
	p->point = create_fvec3(&tmp, scene, str);
	check_space(tmp, 0, str, scene);
	p->dir = create_fvec3(&tmp, scene, str);
	check_space(tmp, 0, str, scene);
	c = create_vec3(&tmp, scene, str);
	check_plane_value(p, scene, c, str);
	scene->nb_object += 1;
	p->n_object = scene->nb_object;
}

void	fill_sphere(char *str, t_sphere *sphere, t_scene *scene)
{
	int		i;
	char	*tmp;
	t_vec3	c;

	i = 0;
	while (str[i] && (!(str[i] >= '0' && str[i] <= '9') && str[i] != '-'))
		i++;
	if (str[i] == '\0')
		error("Sphere : no input", scene, str);
	tmp = &str[i];
	sphere->center = create_fvec3(&tmp, scene, str);
	check_space(tmp, 0, str, scene);
	sphere->diameter = ft_strtod(tmp, &tmp);
	c = create_vec3(&tmp, scene, str);
	if ((c.b < 0 || c.b > 255) || (c.g < 0 || c.g > 255)
		|| (c.r < 0 || c.r > 255))
		error("Sphere : color", scene, str);
	sphere->color.x = (double)c.r / 255;
	sphere->color.y = (double)c.g / 255;
	sphere->color.z = (double)c.b / 255;
	scene->nb_object += 1;
	sphere->n_object = scene->nb_object;
}
