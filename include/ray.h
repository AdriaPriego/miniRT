/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 12:31:34 by apriego-          #+#    #+#             */
/*   Updated: 2023/12/19 01:54:21 by fbosch           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "vec3.h"

typedef struct s_ray
{
	t_point3	orig;
	t_vec3		dir;
}	t_ray;

#endif
