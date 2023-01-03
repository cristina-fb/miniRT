/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_cleaners.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:23:12 by jalvarad          #+#    #+#             */
/*   Updated: 2023/01/03 20:40:53 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	sphere_cleaner(t_sphere *sphere)
{
	if (!sphere)
		return ;
	free(sphere->center);
	free(sphere->rgb);
	free(sphere);
}

void	plane_cleaner(t_plane *plane)
{
	if (!plane)
		return ;
	free(plane->point);
	free(plane->normal);
	free(plane->rgb);
	free(plane);
}

void	cylinder_cleaner(t_cylinder *cylinder)
{
	if (!cylinder)
		return ;
	free(cylinder->center);
	free(cylinder->vector);
	free(cylinder->ba);
	free(cylinder->bb);
	free(cylinder->rgb);
	free(cylinder);
}
