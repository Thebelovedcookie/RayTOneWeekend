/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 15:37:56 by mmahfoud          #+#    #+#             */
/*   Updated: 2023/11/16 09:51:48 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*array;
	size_t		n;

	n = nmemb * size;
	if (n && (n / nmemb != size))
		return (NULL);
	array = (void *)malloc(n);
	if (!(array))
		return (NULL);
	ft_bzero(array, n);
	return (array);
}
