/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:30:53 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/06 21:11:58 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

typedef struct s_vec2
{
	double	x;
	double	y;
}				t_vec2;

typedef struct s_vec3
{
	int	red;
	int	green;
	int	blue;
}				t_vec3;

typedef struct s_fvec3
{
	double	x;
	double	y;
	double	z;
}				t_fvec3;

#endif