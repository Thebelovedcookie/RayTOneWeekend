/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_formule.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <mmahfoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:33:56 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/24 14:11:25 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_fvec3	dive(t_fvec3 a, double b)
{
	double	c;
	t_fvec3	d;

	c = 1 / b;
	d.x = c * a.x;
	d.y = c * a.y;
	d.z = c * a.z;
	return (d);
}

t_fvec3	negat(t_fvec3 a)
{
	t_fvec3	d;

	d.x = -a.x;
	d.y = -a.y;
	d.z = -a.z;
	return (d);
}

t_fvec3	sub(t_fvec3 a, t_fvec3 b)
{
	t_fvec3	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

t_fvec3	sum(t_fvec3 a, t_fvec3 b)
{
	t_fvec3	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_fvec3	x_vec3(t_fvec3 a, t_fvec3 b)
{
	t_fvec3	c;

	c.x = a.x * b.x;
	c.y = a.y * b.y;
	c.z = a.z * b.z;
	return (c);
}

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

double	length(t_fvec3 a)
{
	return (sqrt(length_squared(a)));
}

double	length_squared(t_fvec3 a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

t_fvec3	normalized(t_fvec3 a)
{
	return (dive(a, length(a)));
}

t_fvec3	normal_at(t_sphere *sphere, t_fvec3 point)
{
	return (normalized(sub(point, sphere->center)));
}