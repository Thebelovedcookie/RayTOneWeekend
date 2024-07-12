/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:10:14 by mmahfoud          #+#    #+#             */
/*   Updated: 2023/11/16 10:00:37 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int			i;
	const char	*finder;
	int			size;

	size = ft_strlen((char *)s);
	i = 0;
	c = c % 256;
	if (c < 0)
		c = c + 256;
	while (i <= size)
	{
		if (s[i] == c)
		{
			finder = &s[i];
			return ((char *)finder);
		}
		i++;
	}
	return (NULL);
}
