/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:55:31 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/04/17 13:11:18 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	int		i;
	int		j;
	int		size;

	if (!(s1))
		return (NULL);
	j = 0;
	size = (ft_strlen((char *)s1)) + (ft_strlen((char *)s2)) + 1;
	new_s = (char *)malloc(size * sizeof(char));
	if (!(new_s))
		return (NULL);
	i = -1;
	while (s1[++i])
		new_s[i] = s1[i];
	while (s2[j])
	{
		new_s[i] = s2[j];
		i++;
		j++;
	}
	new_s[i] = '\0';
	return (new_s);
}
