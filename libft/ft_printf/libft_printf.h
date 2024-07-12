/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_printf.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:58:42 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/02/07 11:59:19 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_PRINTF_H
# define LIBFT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *input, ...);
void	ft_input(char c, va_list args, int *n);
void	ft_putchar(int c, int *n);
void	ft_put_hexa(long unsigned int number, int *n, int c);
void	ft_putstr_printf(char *str, int *n);
void	ft_putnbr(long int nbr, int *n, char boolean);
void	ft_put_ptr(long unsigned int ptr, int *n);

#endif
