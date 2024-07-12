/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:08:27 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/01 20:43:00 by mmahfoud         ###   ########.fr       */
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
		error("Ambient : no input", scene);
	tmp = &str[i];
	scene->ambi.ratio = ft_strtod(tmp, &tmp);
	color = (t_vec3){(int)ft_strtod(tmp, &tmp), \
		(int)ft_strtod(tmp, &tmp), (int)ft_strtod(tmp, &tmp)};
	if (scene->ambi.ratio < 0.0 || scene->ambi.ratio > 1.0)
		error("Ambient : ratio", scene);
	if ((color.blue < 0 || color.blue > 255)
		|| (color.green < 0 || color.green > 255)
		|| (color.red < 0 || color.red > 255))
		error("Ambient : color", scene);
	scene->ambi.color.x = (double)color.red / 255;
	scene->ambi.color.y = (double)color.green / 255;
	scene->ambi.color.z = (double)color.blue / 255;
}

void	fill_camera(char *str, t_scene *scene)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && (!(str[i] >= '0' && str[i] <= '9') && str[i] != '-'))
		i++;
	if (str[i] == '\0')
		error("Camera : no input", scene);
	tmp = &str[i];
	scene->cam.view_point = (t_fvec3){ft_strtod(tmp, &tmp),
		ft_strtod(tmp, &tmp), ft_strtod(tmp, &tmp)};
	scene->cam.normalize = (t_fvec3){ft_strtod(tmp, &tmp),
		ft_strtod(tmp, &tmp), ft_strtod(tmp, &tmp)};
	scene->cam.fov = (int)ft_strtod(tmp, &tmp);
	if ((scene->cam.normalize.x < -1.0 || scene->cam.normalize.x > 1.0)
		|| (scene->cam.normalize.y < -1.0 || scene->cam.normalize.y > 1.0)
		|| (scene->cam.normalize.z < -1.0 || scene->cam.normalize.z > 1.0))
		error("Camera : normalize", scene);
	if (scene->cam.fov < 0 || scene->cam.fov > 180)
		error("Camera : fov", scene);
}

void	fill_light(char *str, t_scene *scene)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && (!(str[i] >= '0' && str[i] <= '9') && str[i] != '-'))
		i++;
	if (str[i] == '\0')
		error("Light : no input", scene);
	tmp = &str[i];
	scene->light.light_point = (t_fvec3){ft_strtod(tmp, &tmp),
		ft_strtod(tmp, &tmp), ft_strtod(tmp, &tmp)};
	scene->light.brightness = ft_strtod(tmp, &tmp);
	if (scene->light.brightness < 0.0 || scene->light.brightness > 1.0)
		error("Light: brightness", scene);
}

void	fill_sphere(char *str, t_sphere *sphere, t_scene *scene)
{
	int		i;
	char	*tmp;
	t_vec3	color;

	i = 0;
	while (str[i] && (!(str[i] >= '0' && str[i] <= '9') && str[i] != '-'))
		i++;
	if (str[i] == '\0')
		error("Sphere : no input", scene);
	tmp = &str[i];
	sphere->center = (t_fvec3){ft_strtod(tmp, &tmp),
		ft_strtod(tmp, &tmp), ft_strtod(tmp, &tmp)};
	sphere->diameter = ft_strtod(tmp, &tmp);
	color = (t_vec3){(int)ft_strtod(tmp, &tmp),
		(int)ft_strtod(tmp, &tmp), (int)ft_strtod(tmp, &tmp)};
	if ((color.blue < 0 || color.blue > 255)
		|| (color.green < 0 || color.green > 255)
		|| (color.red < 0 || color.red > 255))
		error("Ambient : color", scene);
	sphere->color.x = (double)color.red / 255;
	sphere->color.y = (double)color.green / 255;
	sphere->color.z = (double)color.blue / 255;
}

void	fill_plane(char *str, t_plane *plane, t_scene *scene)
{
	int		i;
	char	*tmp;
	t_vec3	color;

	i = 0;
	while (str[i] && (!(str[i] >= '0' && str[i] <= '9') && str[i] != '-'))
		i++;
	if (str[i] == '\0')
		error("Plane: no input", scene);
	tmp = &str[i];
	plane->point = (t_fvec3){ft_strtod(tmp, &tmp),
		ft_strtod(tmp, &tmp), ft_strtod(tmp, &tmp)};
	plane->normalize = (t_fvec3){ft_strtod(tmp, &tmp),
		ft_strtod(tmp, &tmp), ft_strtod(tmp, &tmp)};
	color = (t_vec3){(int)ft_strtod(tmp, &tmp),
		(int)ft_strtod(tmp, &tmp), (int)ft_strtod(tmp, &tmp)};
	if ((plane->normalize.x < -1.0 || plane->normalize.x > 1.0)
		|| (plane->normalize.y < -1.0 || plane->normalize.y > 1.0)
		|| (plane->normalize.z < -1.0 || plane->normalize.z > 1.0))
		error("Plane : normalize", scene);
	if ((color.blue < 0 || color.blue > 255)
		|| (color.green < 0 || color.green > 255)
		|| (color.red < 0 || color.red > 255))
		error("Plane : color", scene);
	plane->color.x = (double)color.red / 255;
	plane->color.y = (double)color.green / 255;
	plane->color.z = (double)color.blue / 255;
}

void	fill_cylindre(char *str, t_cylindre *cylindre, t_scene *scene)
{
	int		i;
	char	*tmp;
	t_vec3	color;

	i = 0;
	while (str[i] && (!(str[i] >= '0' && str[i] <= '9') && str[i] != '-'))
		i++;
	if (str[i] == '\0')
		error("Cylindre : no input", scene);
	tmp = &str[i];
	cylindre->center = (t_fvec3){ft_strtod(tmp, &tmp), ft_strtod(tmp, &tmp),
		ft_strtod(tmp, &tmp)};
	cylindre->normalize = (t_fvec3){ft_strtod(tmp, &tmp), ft_strtod(tmp, &tmp),
		ft_strtod(tmp, &tmp)};
	cylindre->diameter = ft_strtod(tmp, &tmp);
	cylindre->height = ft_strtod(tmp, &tmp);
	color = (t_vec3){(int)ft_strtod(tmp, &tmp),
		(int)ft_strtod(tmp, &tmp), (int)ft_strtod(tmp, &tmp)};
	if ((cylindre->normalize.x < -1.0 || cylindre->normalize.x > 1.0)
		|| (cylindre->normalize.y < -1.0 || cylindre->normalize.y > 1.0)
		|| (cylindre->normalize.z < -1.0 || cylindre->normalize.z > 1.0))
		error("cylindre : normalize", scene);
	if ((color.blue < 0 || color.blue > 255) || (color.green < 0
			|| color.green > 255) || (color.red < 0 || color.red > 255))
		error("cylindre : color", scene);
	cylindre->color.x = (double)color.red / 255;
	cylindre->color.y = (double)color.green / 255;
	cylindre->color.z = (double)color.blue / 255;
}
