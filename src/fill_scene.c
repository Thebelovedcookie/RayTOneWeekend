/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:08:27 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/24 23:15:21 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	fill_ambient_lightning(char *str, t_scene *scene)
{
	int		i;
	char	*tmp;
	t_vec3	color;

	i = 0;
	while (str[i] && (!(str[i] >= '0' && str[i] <= '9') && str[i] != '-'))
		i++;
	if (str[i] == '\0')
		error("Ambient : no input", scene, str);
	tmp = &str[i];
	scene->ambi.ratio = ft_strtod(tmp, &tmp);
	check_space(tmp, 0, str, scene);
	color = create_vec3(&tmp, scene, str);
	if (scene->ambi.ratio < 0.0 || scene->ambi.ratio > 1.0)
		error("Ambient : ratio", scene, str);
	if ((color.b < 0 || color.b > 255)
		|| (color.g < 0 || color.g > 255)
		|| (color.r < 0 || color.r > 255))
		error("Ambient : color", scene, str);
	scene->ambi.color.x = (double)color.r / 255;
	scene->ambi.color.y = (double)color.g / 255;
	scene->ambi.color.z = (double)color.b / 255;
}

void	fill_camera(char *str, t_scene *scene)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && (!(str[i] >= '0' && str[i] <= '9') && str[i] != '-'))
		i++;
	if (str[i] == '\0')
		error("Camera : no input", scene, str);
	tmp = &str[i];
	scene->cam.view_point = create_fvec3(&tmp, scene, str);
	check_space(tmp, 0, str, scene);
	scene->cam.normalize = create_fvec3(&tmp, scene, str);
	check_space(tmp, 0, str, scene);
	scene->cam.fov = (int)ft_strtod(tmp, &tmp);
	if ((scene->cam.normalize.x < -1.0 || scene->cam.normalize.x > 1.0)
		|| (scene->cam.normalize.y < -1.0 || scene->cam.normalize.y > 1.0)
		|| (scene->cam.normalize.z < -1.0 || scene->cam.normalize.z > 1.0))
		error("Camera : normalize", scene, str);
	if (scene->cam.fov < 0 || scene->cam.fov > 180)
		error("Camera : fov", scene, str);
}

void	fill_light(char *str, t_scene *scene)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && (!(str[i] >= '0' && str[i] <= '9') && str[i] != '-'))
		i++;
	if (str[i] == '\0')
		error("Light : no input", scene, str);
	tmp = &str[i];
	scene->light.light_point = create_fvec3(&tmp, scene, str);
	check_space(tmp, 0, str, scene);
	scene->light.brightness = ft_strtod(tmp, &tmp);
	if (scene->light.brightness < 0.0 || scene->light.brightness > 1.0)
		error("Light : brightness", scene, str);
}
