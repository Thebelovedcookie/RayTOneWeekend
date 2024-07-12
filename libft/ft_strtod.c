/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:23:35 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/06/21 16:09:56 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>
#include <stdio.h>

static double	ft_strtod_part2(char *nptr, int *i, int clic, int res);

double	ft_strtod(char *nptr, char **endptr)
{
	double	result;
	double	clic;
	int		i;
	double	res;

	i = 0;
	clic = 1.0;
	result = 0;
	while (nptr[i] && ((nptr[i] >= 9 && nptr[i] <= 13) || (nptr[i] == 32)
			|| (nptr[i] == ',')))
		i++;
	if (nptr[i] && (nptr[i] == '-' || nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			clic *= -1.0;
		i++;
	}
	while (nptr[i] && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		result = result * 10 + (nptr[i] - 48);
		i++;
	}
	res = ft_strtod_part2(nptr, &i, clic, result);
	(*endptr) += i;
	return (res);
}

static double	ft_strtod_part2(char *nptr, int *i, int clic, int res)
{
	int	result;
	int	count;

	count = 0;
	result = res;
	if (nptr[*i] == '.')
		(*i)++;
	else
		return (result * clic);
	while (nptr[*i] && (nptr[*i] >= '0' && nptr[*i] <= '9'))
	{
		result = result * 10 + (nptr[*i] - 48);
		(*i)++;
		count++;
	}
	return (round(result * clic) / pow(10.0, count));
}
