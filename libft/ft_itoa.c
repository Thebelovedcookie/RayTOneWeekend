/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 09:12:55 by mmahfoud          #+#    #+#             */
/*   Updated: 2023/11/13 10:00:26 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_count(int nb)
{
	int	count;

	count = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
		count++;
	while ((nb / 10) != 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count + 1);
}

char	*ft_itoa(int nb)
{
	int		count;
	char	*c_nb;

	count = ft_count(nb);
	c_nb = malloc((count + 1) * sizeof(char));
	if (!(c_nb))
		return (NULL);
	c_nb[count] = '\0';
	if (nb < 0)
		c_nb[0] = '-';
	if (nb == 0)
		c_nb[0] = 48;
	while (nb != 0)
	{
		if (nb < 0)
			c_nb[count - 1] = ((nb % 10) * (-1)) + 48;
		else
			c_nb[count - 1] = (nb % 10) + 48;
		count--;
		nb = nb / 10;
	}
	return (c_nb);
}
