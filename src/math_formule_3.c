/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_formule_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sonouelg <sonouelg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:33:56 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/25 12:57:25 by sonouelg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
