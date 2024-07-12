/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:52:29 by mmahfoud          #+#    #+#             */
/*   Updated: 2023/11/15 10:23:42 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		nb *= -1;
	}
	if (!(nb <= 9))
	{
		ft_putnbr_fd((nb / 10), fd);
		ft_putchar_fd(((nb % 10) + 48), fd);
	}
	if (nb <= 9)
		ft_putchar_fd(nb + 48, fd);
}
