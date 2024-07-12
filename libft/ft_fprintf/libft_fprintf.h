/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_fprintf.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:56:38 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/02/07 11:56:46 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_FPRINTF_H
# define LIBFT_FPRINTF_H

# include "../libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

int		ft_fprintf(int stream, const char *input, ...);
void	ft_finput(int stream, char c, va_list args, int *n);
void	ft_fputchar(int stream, int c, int *n);
void	ft_fput_hexa(int stream, long unsigned int number, int *n, int c);
void	ft_fputstr_printf(int stream, char *str, int *n);
void	ft_fputnbr(int stream, long int nbr, int *n, char boolean);
void	ft_fput_ptr(int stream, long unsigned int ptr, int *n);

#endif
