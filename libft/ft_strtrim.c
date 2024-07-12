/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 12:11:46 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/18 12:51:26 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_is_sep(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_start(char const *s1, char const *set)
{
	int	start;

	start = 0;
	while (ft_is_sep(s1[start], set) == 1 && s1)
		start++;
	return (start);
}

static int	ft_end(char const *s1, char const *set, int start)
{
	int	end;

	end = ft_strlen(s1) - 1;
	while (ft_is_sep(s1[end], set) == 1 && end > start && s1)
		end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*new_s;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	start = ft_start(s1, set);
	end = ft_end(s1, set, start);
	new_s = malloc(((end - start) + 2) * sizeof(char));
	if (!new_s)
		return (NULL);
	while (i <= (end - start))
	{
		new_s[i] = s1[i + start];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
