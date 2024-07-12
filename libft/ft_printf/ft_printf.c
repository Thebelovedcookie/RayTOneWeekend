/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:57:42 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/02/07 11:58:09 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"
#include "../libft.h"
#include <stdio.h>

void	ft_input(char c, va_list args, int *n)
{
	if (c == 'c')
		ft_putchar(va_arg(args, int), n);
	if (c == 's')
		ft_putstr_printf(va_arg(args, char *), n);
	if (c == 'p')
		ft_put_ptr(va_arg(args, long unsigned int), n);
	if (c == 'd')
		ft_putnbr(va_arg(args, int), n, 'f');
	if (c == 'i')
		ft_putnbr(va_arg(args, int), n, 'f');
	if (c == 'u')
		ft_putnbr(va_arg(args, unsigned int), n, 't');
	if (c == 'x')
		ft_put_hexa(va_arg(args, unsigned int), n, 0);
	if (c == 'X')
		ft_put_hexa(va_arg(args, unsigned int), n, 1);
}

int	ft_printf(const char *input, ...)
{
	va_list	args;
	int		i;
	int		n;

	va_start(args, input);
	i = 0;
	n = 0;
	while (input[i])
	{
		if (input[i] != '%')
			ft_putchar(input[i], &n);
		if (input[i] == '%')
		{
			if (input[i + 1] == '%')
				ft_putchar('%', &n);
			else
				ft_input(input[i + 1], args, &n);
			i++;
		}
		i++;
	}
	va_end(args);
	return (n);
}
