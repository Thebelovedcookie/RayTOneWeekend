/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 09:47:02 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/02/28 16:51:29 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

typedef struct s_elem
{
	char			*data;
	int				size_data;
	struct s_elem	*next;
}		t_elem;

void	free_elem(t_elem **begin_list, t_elem *current);
void	ft_read(t_elem **begin_list, int fd, int *readed);
int		check_for_bn(t_elem **begin_list, int readed);
char	*init_str(int size_str);
char	*extract(t_elem **begin_list, int readed);
void	clean_struct(t_elem **begin_list);
void	clean_str(t_elem *current, int erase);
char	*treat_text(int fd, t_elem **begin_list, int *readed);
char	*get_next_line(int fd);
void	add_last(t_elem **begin_list, char *tmp, int *readed, t_elem *new);

#endif
