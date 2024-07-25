/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_formule_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonouelg <sonouelg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:33:56 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/25 12:39:36 by sonouelg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_fvec3	dmul(double a, t_fvec3 b)
{
	t_fvec3	c;

	c.x = a * b.x;
	c.y = a * b.y;
	c.z = a * b.z;
	return (c);
}

t_fvec3	cross(t_fvec3 a, t_fvec3 b)
{
	t_fvec3	c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
	return (c);
}

double	dot(t_fvec3 a, t_fvec3 b)
{
	double	c;

	c = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return (c);
}
