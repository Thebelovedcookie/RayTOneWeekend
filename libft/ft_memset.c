/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:02:46 by mmahfoud          #+#    #+#             */
/*   Updated: 2023/11/07 11:13:22 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*temp;

	temp = s;
	i = 0;
	while (i < n)
	{
		temp[i] = (unsigned char) c;
		i++;
	}
	return (temp);
}
