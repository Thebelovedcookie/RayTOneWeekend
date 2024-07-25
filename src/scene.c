/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:18:20 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/25 11:40:16 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	open_my_file(char *file_name)
{
	int	fd;
	int	size;

	size = ft_strlen(file_name);
	if (ft_strncmp(&(file_name)[size - 3], ".rt", 4) != 0)
	{
		ft_fprintf(2, "I'm taking only .rt extension.\n");
		exit(EXIT_FAILURE);
	}
	fd = open(file_name, O_RDONLY);
	if (fd <= 0)
	{
		ft_fprintf(2, "Theres is an issues while opening the file\n");
		exit(EXIT_FAILURE);
	}
	return (fd);
}

t_scene	*read_my_file(int fd)
{
	char	*str;
	t_scene	*scene;

	scene = create_scene();
	scene->fd = fd;
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		check_my_line(str, scene);
		free(str);
	}
	return (scene);
}

int	check_my_line(char *str, t_scene *scene)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (ft_strncmp(&str[i], "\n", 2) == 0)
		return (1);
	else if (str[i] == 'A')
		fill_ambient_lightning(str, scene);
	else if (str[i] == 'C')
		fill_camera(str, scene);
	else if (str[i] == 'L')
		fill_light(str, scene);
	else if (ft_strncmp(&str[i], "sp", 2) == 0)
		add_sphere(str, scene);
	else if (ft_strncmp(&str[i], "pl", 2) == 0)
		add_plane(str, scene);
	else if (ft_strncmp(&str[i], "cy", 2) == 0)
		add_cylinder(str, scene);
	else
		ft_fprintf(2, "Error : bad line format.\n");
	return (0);
}
