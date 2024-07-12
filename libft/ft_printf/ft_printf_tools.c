/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:57:07 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/02/07 11:57:32 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"
#include "../libft.h"
#include <unistd.h>
#include <stdio.h>

void	ft_putchar(int c, int *n)
{
	write(1, &c, 1);
	*n += 1;
}

void	ft_putstr_printf(char *str, int *n)
{
	if (!str)
	{
		ft_putstr_printf("(null)", n);
		return ;
	}
	write(1, str, ft_strlen(str));
	*n += ft_strlen(str);
}

void	ft_putnbr(long int nbr, int *n, char boolean)
{
	long	number;

	number = nbr;
	if (boolean == 'f' && number < 0)
	{
		number *= -1;
		ft_putchar('-', n);
	}
	if (!(number >= 0 && number <= 9))
	{
		ft_putnbr(number / 10, n, boolean);
		ft_putchar((number % 10 + 48), n);
	}
	if (number >= 0 && number <= 9)
		ft_putchar((number + 48), n);
}

void	ft_put_hexa(long unsigned int number, int *n, int c)
{
	char	*base;

	if (c == 0)
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (number <= 15)
		ft_putchar(base[0 + number], n);
	if (number > 15)
	{
		ft_put_hexa(number / 16, n, c);
		ft_putchar(base[0 + number % 16], n);
	}
}

void	ft_put_ptr(long unsigned int ptr, int *n)
{
	if (!ptr)
	{
		ft_putstr_printf("(nil)", n);
		return ;
	}
	ft_putstr_printf("0x", n);
	ft_put_hexa(ptr, n, 0);
}
