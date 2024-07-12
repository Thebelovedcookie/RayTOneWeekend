/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:54:24 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/02/07 11:57:02 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_fprintf.h"

void	ft_fputchar(int stream, int c, int *n)
{
	write(stream, &c, 1);
	*n += 1;
}

void	ft_fputstr_printf(int stream, char *str, int *n)
{
	if (!str)
	{
		ft_fputstr_printf(stream, "(null)", n);
		return ;
	}
	write(stream, str, ft_strlen(str));
	*n += ft_strlen(str);
}

void	ft_fputnbr(int stream, long int nbr, int *n, char boolean)
{
	long	number;

	number = nbr;
	if (boolean == 'f' && number < 0)
	{
		number *= -1;
		ft_fputchar(stream, '-', n);
	}
	if (!(number >= 0 && number <= 9))
	{
		ft_fputnbr(stream, number / 10, n, boolean);
		ft_fputchar(stream, (number % 10 + 48), n);
	}
	if (number >= 0 && number <= 9)
		ft_fputchar(stream, (number + 48), n);
}

void	ft_fput_hexa(int stream, long unsigned int number, int *n, int c)
{
	char	*base;

	if (c == 0)
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (number <= 15)
		ft_fputchar(stream, base[0 + number], n);
	if (number > 15)
	{
		ft_fput_hexa(stream, number / 16, n, c);
		ft_fputchar(stream, base[0 + number % 16], n);
	}
}

void	ft_fput_ptr(int stream, long unsigned int ptr, int *n)
{
	if (!ptr)
	{
		ft_fputstr_printf(stream, "(nil)", n);
		return ;
	}
	ft_fputstr_printf(stream, "0x", n);
	ft_fput_hexa(stream, ptr, n, 0);
}
