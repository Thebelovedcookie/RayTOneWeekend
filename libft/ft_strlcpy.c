/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 09:17:34 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/04/27 17:57:31 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*LIBRARY
     size_t
     strlcpy(char *dst, const char *src,
         size_t size);

DESCRIPTION
     The strlcpy() copy strings.
     Unlike
     those functions, strlcpy() and strlcat()
     take the full size of the buffer (not just
     the length) and guarantee to NUL-terminate
     the result (as long as size is larger than
     0 or, in the case of strlcat(), as long as
     there is at least one byte free in dst).
     Note that a byte for the NUL should be in‐
     cluded in size.  Also note that strlcpy()
     and strlcat() only operate on true “C”
     strings.  This means that for strlcpy()
     src must be NUL-terminated and for
     strlcat() both src and dst must be NUL-
     terminated.*/

#include <stdlib.h>
#include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (src[count] != '\0')
		count++;
	if (size > 0)
	{
		while ((i < size - 1) && (src[i]))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (count);
}
