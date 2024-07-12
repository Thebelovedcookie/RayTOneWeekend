/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:13:54 by mmahfoud          #+#    #+#             */
/*   Updated: 2023/11/16 09:01:52 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = (unsigned char *)s;
	i = 0;
	c = c % 256;
	if (c < 0)
		c = c - 256;
	while (i < n)
	{
		if (tmp[i] == (unsigned char)c)
		{
			return (&tmp[i]);
		}
		i++;
	}
	return (NULL);
}
