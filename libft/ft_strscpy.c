/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strscpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:38:14 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/03/06 12:41:32 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*fonction qui permet de copier a partir de l'index start 
et ce jusqu'a la fin de la string*/

void	ft_strscpy(char *dst, char *src, int start)
{
	int	i;

	i = 0;
	if (!src)
	{
		dst = NULL;
		return ;
	}
	while (src[start])
	{
		dst[i] = src[start];
		i++;
		start++;
	}
	dst[i] = '\0';
}
