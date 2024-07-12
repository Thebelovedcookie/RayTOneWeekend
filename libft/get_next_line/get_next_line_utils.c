/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:54:50 by mmahfoud          #+#    #+#             */
/*   Updated: 2023/12/16 12:44:49 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	add_last(t_elem **begin_list, char *tmp, int *readed, t_elem *new)
{
	t_elem	*current;
	int		i;

	i = 0;
	while (i < *readed)
	{
		new->data[i] = tmp[i];
		i++;
	}
	new->data[i] = '\0';
	new->size_data = i + 1;
	new->next = NULL;
	current = *begin_list;
	if (current == NULL)
		*begin_list = new;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new;
	}
}

char	*treat_text(int fd, t_elem **begin_list, int *readed)
{
	int		check_bn;
	char	*str;

	check_bn = 0;
	str = NULL;
	while (check_for_bn(begin_list, *readed) == -1 && *readed == BUFFER_SIZE)
		ft_read(begin_list, fd, readed);
	check_bn = check_for_bn(begin_list, *readed);
	if (check_bn == -1 && *readed < BUFFER_SIZE)
	{
		str = extract(begin_list, *readed);
		if (str == NULL && readed == 0)
		{
			free(str);
			return (NULL);
		}
		clean_struct(begin_list);
	}
	else if (check_bn != -1)
	{
		str = extract(begin_list, *readed);
		clean_struct(begin_list);
	}
	return (str);
}

void	ft_read(t_elem **begin_list, int fd, int *readed)
{
	char	*tmp;
	t_elem	*new;

	tmp = malloc(BUFFER_SIZE * sizeof(char));
	if (!tmp)
		return ;
	*readed = read(fd, tmp, BUFFER_SIZE);
	if (*readed == 0 || *readed < 0)
	{
		free(tmp);
		return ;
	}
	new = malloc(sizeof(t_elem));
	if (new == NULL)
		return ;
	new->data = malloc((*readed + 1) * sizeof(char));
	if (new->data == NULL)
	{
		free(new);
		return ;
	}
	add_last(begin_list, tmp, readed, new);
	free(tmp);
}

int	check_for_bn(t_elem **begin_list, int readed)
{
	t_elem	*tmp;
	int		i;
	int		size_for_init;

	i = 0;
	size_for_init = 0;
	tmp = *begin_list;
	while (tmp)
	{
		while (tmp->data[i])
		{
			if (tmp->data[i] == '\n')
			{
				size_for_init += i;
				return (size_for_init + 1);
			}
			i++;
		}
		size_for_init += tmp->size_data - 1;
		tmp = tmp->next;
		i = 0;
	}
	if (readed < BUFFER_SIZE)
		return (size_for_init + 1);
	return (-1);
}

void	free_elem(t_elem **begin_list, t_elem *current)
{
	free(current->data);
	*begin_list = current->next;
	free(current);
}
