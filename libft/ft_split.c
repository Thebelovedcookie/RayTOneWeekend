/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:08:50 by mmahfoud          #+#    #+#             */
/*   Updated: 2023/11/16 10:02:37 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_size_tab(const char *s, char c)
{
	int	count_sep;
	int	clic;

	count_sep = 0;
	clic = 1;
	while (*s)
	{
		if (*s == c)
		{
			clic = 1;
			s++;
		}
		else if (*s != c && clic == 1)
		{
			count_sep++;
			clic = 0;
			s++;
		}
		else
			s++;
	}
	return (count_sep);
}

void	ft_cpy_word(char const *s, int start, int end, char *dest)
{
	int	i;

	i = 0;
	while (start < end)
	{
		dest[i] = s[start];
		start++;
		i++;
	}
	dest[i] = '\0';
}

char	*ft_malloc_cpy(char const *s, char c, int start)
{
	char	*str;
	int		end;

	end = start;
	while (s[end] != c && s[end] != '\0')
		end++;
	str = malloc(((end - start) + 1) * sizeof(char));
	ft_cpy_word(s, start, end, str);
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		index;
	int		i;

	if (!(s))
		return (NULL);
	index = 0;
	tab = malloc((ft_size_tab(s, c) + 1) * sizeof(char *));
	if (!(tab))
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			tab[index] = ft_malloc_cpy(s, c, i);
			index++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	tab[index] = NULL;
	return (tab);
}
