/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:42:26 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/16 16:00:09 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*init_str(int size_str)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc((size_str + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	while (i <= size_str)
	{
		str[i] = '\0';
		i++;
	}
	return (str);
}

char	*extract(t_elem **begin_list, int readed)
{
	char	*str;
	t_elem	*tmp;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (*begin_list == NULL)
		return (NULL);
	str = init_str(check_for_bn(begin_list, readed));
	tmp = *begin_list;
	while (tmp)
	{
		while (tmp->data[i])
		{
			str[j++] = tmp->data[i];
			if (tmp->data[i] == '\n')
				break ;
			i++;
		}
		tmp = tmp->next;
		i = 0;
	}
	str[j] = '\0';
	return (str);
}

void	clean_struct(t_elem **begin_list)
{
	t_elem	*tmp;
	int		i;

	i = 0;
	tmp = *begin_list;
	while (tmp)
	{
		while (tmp->data[i] != '\n' && tmp->data[i])
			i++;
		if (tmp->data[i] == '\n')
		{
			clean_str(tmp, i + 1);
			if (tmp->size_data == 1)
			{
				free_elem(begin_list, tmp);
				return ;
			}
			*begin_list = tmp;
			return ;
		}
		free_elem(begin_list, tmp);
		tmp = *begin_list;
		i = 0;
	}
	*begin_list = NULL;
}

void	clean_str(t_elem *current, int erase)
{
	int	i;

	i = 0;
	current->size_data -= erase;
	while (current->data[erase])
	{
		current->data[i] = current->data[erase];
		i++;
		erase++;
	}
	current->data[i] = '\0';
}

char	*get_next_line(int fd)
{
	static t_elem		**begin_list = NULL;
	static int			readed = BUFFER_SIZE;
	char				*str;

	str = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (begin_list == NULL)
	{
		begin_list = malloc(sizeof(t_elem *));
		*begin_list = NULL;
	}
	if (*begin_list != NULL)
		str = treat_text(fd, begin_list, &readed);
	else if (*begin_list == NULL)
		str = treat_text(fd, begin_list, &readed);
	if (*begin_list == NULL && readed < BUFFER_SIZE && str == NULL)
	{
		free(*begin_list);
		free(begin_list);
		begin_list = NULL;
		return (NULL);
	}
	return (str);
}
