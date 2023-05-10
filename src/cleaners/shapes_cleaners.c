/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_cleaners.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:23:12 by jalvarad          #+#    #+#             */
/*   Updated: 2023/05/05 18:13:34 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	sphere_cleaner(void *sp)
{
	t_sphere	*sphere;

	sphere = (t_sphere *) sp;
	if (!sphere)
		return ;
	free(sphere->center);
	free(sphere->rgb);
	free(sphere);
}

void	plane_cleaner(void *pl)
{
	t_plane	*plane;

	plane = (t_plane *) pl;
	if (!plane)
		return ;
	free(plane->point);
	free(plane->normal);
	free(plane->rgb);
	free(plane);
}

void	cylinder_cleaner(void *cy)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *) cy;
	if (!cylinder)
		return ;
	free(cylinder->vector);
	free(cylinder->ba);
	free(cylinder->base);
	free(cylinder->rgb);
	free(cylinder);
}

void	torus_cleaner(void *t)
{
	t_torus	*torus;

	torus = (t_torus *) t;
	if (!torus)
		return ;
	free(torus->rgb);
	free(torus->center);
	free(torus->orientation);
	free(torus);
}
