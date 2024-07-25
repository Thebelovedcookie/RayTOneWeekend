/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmahfoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 22:19:28 by mmahfoud          #+#    #+#             */
/*   Updated: 2024/07/24 21:15:06 by mmahfoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_fvec3	ambient(t_fvec3 color, t_material mat, t_w *w)
{
	t_fvec3	ambient;
	t_fvec3	effective_color;

	effective_color = dmul(w->scene->light.brightness, color);
	ambient = dmul(mat.ambient, effective_color);
	return (ambient);
}

void	diffuse(t_fvec3 color, t_w *w, t_phong *phong)
{
	double	light_dot_normal;
	t_light	light;

	light = w->scene->light;
	phong->lightv = normalized(sub(light.light_point,
				phong->intersected_point));
	w->ray.ray_light_origin = phong->intersected_point;
	w->ray.ray_light_direction = normalized(sub(light.light_point,
				phong->intersected_point));
	if (intersect_function_shad(w) == 0)
	{
		phong->shadow = 1;
		return ;
	}
	phong->effective_color = dmul(light.brightness, color);
	light_dot_normal = dot(phong->lightv, phong->normalv);
	if (light_dot_normal < EPSILON)
	{
		phong->diffuse = ((t_fvec3){0.0, 0.0, 0.0});
		return ;
	}
	phong->diffuse = dmul(light_dot_normal,
			dmul(phong->mat.diffuse, phong->effective_color));
}

void	specular(t_phong *phong, t_w *w)
{
	double	specular;
	double	factor;
	double	reflect_dot_eye;
	t_fvec3	reflectv;

	reflectv = reflection(negat(phong->lightv), phong->normalv);
	reflect_dot_eye = dot(reflectv, phong->vector_eye);
	if (reflect_dot_eye <= EPSILON)
	{
		phong->specular = (t_fvec3){0.0, 0.0, 0.0};
		return ;
	}
	factor = pow(reflect_dot_eye, phong->mat.shininess);
	specular = w->scene->light.brightness * phong->mat.specular * factor;
	phong->specular = (t_fvec3){specular, specular, specular};
}

t_fvec3	reflection(t_fvec3 in, t_fvec3 normal)
{
	t_fvec3	a;
	t_fvec3	b;
	t_fvec3	result;
	double	dot_result;

	dot_result = dot(in, normal);
	a = dmul(2, normal);
	b = dmul(dot_result, a);
	result = sub(in, b);
	return (result);
}
