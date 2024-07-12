/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:54:29 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/02/07 11:56:07 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_fprintf.h"

void	ft_finput(int stream, char c, va_list args, int *n)
{
	if (c == 'c')
		ft_fputchar(stream, va_arg(args, int), n);
	if (c == 's')
		ft_fputstr_printf(stream, va_arg(args, char *), n);
	if (c == 'p')
		ft_fput_ptr(stream, va_arg(args, long unsigned int), n);
	if (c == 'd')
		ft_fputnbr(stream, va_arg(args, int), n, 'f');
	if (c == 'i')
		ft_fputnbr(stream, va_arg(args, int), n, 'f');
	if (c == 'u')
		ft_fputnbr(stream, va_arg(args, unsigned int), n, 't');
	if (c == 'x')
		ft_fput_hexa(stream, va_arg(args, unsigned int), n, 0);
	if (c == 'X')
		ft_fput_hexa(stream, va_arg(args, unsigned int), n, 1);
}

int	ft_fprintf(int stream, const char *input, ...)
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
			ft_fputchar(stream, input[i], &n);
		if (input[i] == '%')
		{
			if (input[i + 1] == '%')
				ft_fputchar(stream, '%', &n);
			else
				ft_finput(stream, input[i + 1], args, &n);
			i++;
		}
		i++;
	}
	va_end(args);
	return (n);
}
