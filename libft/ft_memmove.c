/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:10:32 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/05/18 12:50:41 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*NAME
       memmove - copy memory area

SYNOPSIS
       #include <string.h>

       void *memmove(void *dest, const void *src, size_t n);

DESCRIPTION
       The  memmove()  function  copies n bytes from memory area src to memory
       area dest.  The memory areas may overlap: copying takes place as though
       the  bytes in src are first copied into a temporary array that does not
       overlap src or dest, and the bytes are then copied from  the  temporary
       array to dest.*/

#include <stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*t_dest;
	char		*t_src;
	size_t		i;

	if ((!dest) && (!src))
		return (NULL);
	t_dest = (char *)dest;
	t_src = (char *)src;
	i = 0;
	if (t_dest > t_src)
	{
		while (i < n)
		{
			t_dest[n - i - 1] = t_src[n - i - 1];
			i++;
		}
	}
	while (i < n)
	{
		t_dest[i] = t_src[i];
		i++;
	}
	return ((void *) t_dest);
}
