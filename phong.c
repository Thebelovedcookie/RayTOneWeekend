#include "minirt.h"

t_fvec3	ambient(t_fvec3 color, t_material mat, t_window *window)
{
	t_fvec3	ambient;
	t_fvec3	effective_color;

	effective_color = double_x_vec3(window->scene->light.brightness, color);
	ambient = double_x_vec3(mat.ambient, effective_color);
	return (ambient);
}

void	diffuse(t_fvec3 color, t_window *window, t_phong *phong)
{
	double	light_dot_normal;

	phong->lightv = unit_vector(minus_vec3(window->scene->light.light_point,
				phong->intersected_point));
	window->ray.ray_light_origin = phong->intersected_point;
	window->ray.ray_light_direction = minus_vec3(window->scene->light.light_point,
				phong->intersected_point);
	if (intersect_function_shad(window) == 0)
	{
		phong->shadow = 1;
		return ;
	}
	phong->effective_color = double_x_vec3(window->scene->light.brightness, color);
	light_dot_normal = dot_product(phong->lightv, phong->normalv);
	if (light_dot_normal < 0.0)
	{
		phong->diffuse = ((t_fvec3){0.0, 0.0, 0.0});
		return ;
	}
	phong->diffuse = double_x_vec3(light_dot_normal,
			double_x_vec3(phong->mat.diffuse, phong->effective_color));
}

void	specular(t_phong *phong, t_window *window)
{
	double	specular;
	double	factor;
	double	reflect_dot_eye;
	t_fvec3	reflectv;

	reflectv = reflection(negating_vec3(phong->lightv), phong->normalv);
	reflect_dot_eye = dot_product(reflectv, phong->vector_eye);
	if (reflect_dot_eye <= 0.0)
	{
		phong->specular = (t_fvec3){0.0, 0.0, 0.0};
		return ;
	}
	factor = pow(reflect_dot_eye, phong->mat.shininess);
	specular = window->scene->light.brightness * phong->mat.specular * factor;
	phong->specular = (t_fvec3){specular, specular, specular};
}

t_fvec3	reflection(t_fvec3 in, t_fvec3 normal)
{
	t_fvec3	a;
	t_fvec3	b;
	t_fvec3	result;
	double	dot_result;

	dot_result = dot_product(in, normal);
	a = double_x_vec3(2, normal);
	b = double_x_vec3(dot_result, a);
	result = minus_vec3(in, b);
	return (result);
}
