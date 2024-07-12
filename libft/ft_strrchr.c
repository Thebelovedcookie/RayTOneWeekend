/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:39:16 by mmahfoud          #+#    #+#             */
/*   Updated: 2023/11/10 10:28:41 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int			size;
	const char	*finder;

	size = 0;
	c = c % 256;
	if (c < 0)
		c = c - 256;
	while (s[size])
		size++;
	while (size >= 0)
	{
		if (s[size] == c)
		{
			finder = &s[size];
			return ((char *)finder);
		}
		size--;
	}
	finder = NULL;
	return ((char *)finder);
}
