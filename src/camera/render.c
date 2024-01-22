/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:13:17 by fbosch            #+#    #+#             */
/*   Updated: 2024/01/23 00:55:05 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MiniRT.h"

t_color	render_raytrace_mode_reflect(t_scene *scene, const t_ray *r, t_world *hit_obj,
		t_hit *hit_rec, int ray_depth);

void	draw_selection_mask(const t_ray *r, t_scene *scene, t_world *objs,
		int i, int j)
{
	t_hit	hit_rec;

	hit_rec.ray_tmin = BIAS;
	hit_rec.ray_tmax = INT_MAX;
	if (objs == scene->selected)
	{
		if (objs->hit(r, objs->type, &hit_rec))
			scene->select_mask[i + (j * IMG_W)] = WHITE;
		else
			scene->select_mask[i + (j * IMG_W)] = BLACK;
	}
}

t_color	send_ray(const t_ray *r, t_scene *scene, int i, int j)
{
	t_hit	hit_rec;
	t_world	*objs;

	hit_rec.obj = NULL;
	hit_rec.ray_tmin = BIAS;
	hit_rec.ray_tmax = INT_MAX;
	objs = scene->objs;
	while (objs)
	{
		draw_selection_mask(r, scene, objs, i, j);
		if (objs->hit(r, objs->type, &hit_rec))
		{
			hit_rec.ray_tmax = hit_rec.t;
			hit_rec.obj = objs;
		}
		objs = objs->next;
	}
	if (hit_rec.obj)
	{
		if (scene->render_mode == EDIT_MODE)
			return (render_edit_mode(scene, r, &hit_rec));
		else
			return (render_raytrace_mode(scene, r, &hit_rec, RAY_DEPTH));
	}
	return (scene->bg_color);
}

t_color	render_edit_mode(t_scene *scene, const t_ray *r, t_hit *hit_rec)
{
	t_color	color;
	t_vec3	view_dir;
	double	a;

	view_dir = product_vec3_r(&r->dir, -1);
	view_dir = unit_vector(&view_dir);
	a = dot(&view_dir, &hit_rec->normal) * 0.5;
	color = product_vec3_r(&hit_rec->obj->materia.color, 0.5);
	color = (t_color){color.x + a, color.y + a, color.z + a};
	if (hit_rec->obj == scene->selected)
		color = (t_color){hit_rec->normal.x, hit_rec->normal.y,
			hit_rec->normal.z};
	return (color);
}

// FIX BIAS FOR CONES
void	calc_shadow_ray(t_ray *shadow_ray, t_light *lights, t_hit *hit_rec)
{
	shadow_ray->orig = product_vec3_r(&hit_rec->normal, BIAS * 2);
	shadow_ray->orig = add_vec3(&hit_rec->p, &shadow_ray->orig);
	shadow_ray->dir = substract_vec3(&lights->center, &shadow_ray->orig);
	shadow_ray->len_sqrd = length_squared(&shadow_ray->dir);
	shadow_ray->dir = unit_vector(&shadow_ray->dir);
}

// reflected_ray.dir = v - 2*dot(v,n)*n;
t_ray	calc_reflected_ray(t_hit *hit_rec, const t_ray *r)
{
	t_ray	reflected;
	t_vec3	dir;

	reflected.orig = product_vec3_r(&hit_rec->normal, BIAS);
	reflected.orig = add_vec3(&hit_rec->p, &reflected.orig);
	dir = unit_vector(&r->dir);
	reflected.dir = product_vec3_r(&hit_rec->normal, 2 * dot(&dir, &hit_rec->normal)); //unit vectors or not
	reflected.dir = substract_vec3(&dir, &reflected.dir); //unit vectors or not
	return (reflected);
}

t_color	render_raytrace_mode(t_scene *scene, const t_ray *r, t_hit *hit_rec, int ray_depth)
{
	t_color	pxl_color;
	t_color	diffuse_light;
	t_color	specular_light;
	t_ray	r_light;
	t_light	*lights;

	if (ray_depth <= 0)
		return ((t_color){0, 0, 0});
	pxl_color = hit_rec->obj->get_color(&hit_rec->p, hit_rec->obj);
	pxl_color = calc_ambient_light(&scene->amblight.color, &pxl_color,
			scene->amblight.ratio);
	lights = scene->light;
	while (lights)
	{
		calc_shadow_ray(&r_light, lights, hit_rec);
		if (calc_hard_shadows(scene->objs, &r_light, hit_rec) == false)
		{
			diffuse_light = calc_diffuse_light(lights, &r_light, hit_rec);
			specular_light = calc_specular_light(lights, r, &r_light, hit_rec);
			pxl_color = add_vec3(&pxl_color, &diffuse_light);
			pxl_color = add_vec3(&pxl_color, &specular_light);
		}
		lights = lights->next;
	}
	t_color	reflect;
	t_ray	r_reflected;
	reflect = (t_color){0, 0, 0};
	{
		if (hit_rec->obj->materia.metallic > 0.0)
		{
			r_reflected = calc_reflected_ray(hit_rec, r);
			
			t_world	*obj;
			t_hit	r_hit_rec;

			obj = scene->objs;
			r_hit_rec.obj = NULL;
			r_hit_rec.ray_tmin = BIAS;
			r_hit_rec.ray_tmax = INT_MAX;
			while (obj)
			{
				if (obj->hit(&r_reflected, obj->type, &r_hit_rec))
				{
					r_hit_rec.ray_tmax = r_hit_rec.t;
					r_hit_rec.obj = obj;
				}
				obj = obj->next;
			}
			if (r_hit_rec.obj)
				reflect = render_raytrace_mode(scene, &r_reflected, &r_hit_rec, ray_depth - 1);
			else
				reflect = (t_color){0, 0, 0};
		}
		product_vec3(&reflect, hit_rec->obj->materia.metallic);
	}
	product_vec3(&pxl_color, 1 - hit_rec->obj->materia.metallic);
	pxl_color = add_vec3(&pxl_color, &reflect);
	return (pxl_color);
}

t_color	render_raytrace_mode_reflect(t_scene *scene, const t_ray *r, t_world *hit_obj,
		t_hit *hit_rec, int ray_depth)
{
	t_color	albedo;
	t_color	diffuse_light;
	t_color	specular_light;
	t_ray	r_light;
	t_light	*lights;

	albedo = hit_obj->get_color(&hit_rec->p, hit_obj);
	albedo = calc_ambient_light(&scene->amblight.color, &albedo,
			scene->amblight.ratio);
	lights = scene->light;
	while (lights)
	{
		calc_shadow_ray(&r_light, lights, hit_rec);
		if (calc_hard_shadows(scene->objs, &r_light, hit_rec) == false)
		{
			diffuse_light = calc_diffuse_light(lights, &r_light, hit_rec);
			specular_light = calc_specular_light(lights, r, &r_light, hit_rec);
			albedo = add_vec3(&albedo, &diffuse_light);
			albedo = add_vec3(&albedo, &specular_light);
		}
		lights = lights->next;
	}
	albedo = product_vec3_r(&albedo, 0.1);
	
	
	t_color	reflection = {0, 0, 0};

	t_ray	reflected;

	reflected.orig = product_vec3_r(&hit_rec->normal, BIAS);
	reflected.orig = add_vec3(&hit_rec->p, &reflected.orig);
	
	t_vec3 dir = unit_vector(&r->dir);
	reflected.dir = product_vec3_r(&hit_rec->normal, 2 * dot(&dir, &hit_rec->normal));
	reflected.dir = substract_vec3(&dir, &reflected.dir);
	
	t_world *objs = scene->objs;
	t_world	*hit_obj2;
	t_hit	hit_rec2;

	hit_rec2.ray_tmin = BIAS;
	hit_rec2.ray_tmax = INT_MAX;
	hit_obj2 = NULL;
	while (objs)
	{
		if (hit_obj->hit(&reflected, objs->type, &hit_rec2))
		{
			hit_rec2.ray_tmax = hit_rec2.t;
			hit_obj2 = objs;
		}
		objs = objs->next;
	}
	if (ray_depth <= 0)
		return ((t_color){0, 0, 0});
	if (hit_obj2)
	{
		t_color tmp_col = render_raytrace_mode_reflect(scene, &reflected, hit_obj2, &hit_rec2, ray_depth - 1);
		reflection = add_vec3(&reflection, &tmp_col);
	}
	reflection = product_vec3_r(&reflection, 0.9);
	/* if (ray_depth == 10)
		reflection = division_vec3_r(&reflection, ray_depth); */
	t_color tmp = add_vec3(&albedo, &reflection);
	return (tmp);
}


/* if (obj->hit)
{
	function render_pixel(max_depth)
	{
		albedo color + reflection color;
	}
} */
