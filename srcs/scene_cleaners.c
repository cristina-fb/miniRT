/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_cleaners.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:01:53 by jalvarad          #+#    #+#             */
/*   Updated: 2022/12/26 17:44:56 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	ambient_light_cleaner(t_ambient *ambient)
{
	if (!ambient)
		return ;
	free(ambient->rgb);
	ambient->rgb = NULL;
}

void	camera_cleaner(t_camera *camera)
{
	if (!camera)
		return ;
	free(camera->center);
	camera->center = NULL;
	free(camera->orientation);
	camera->orientation = NULL;
}

void	light_cleaner(t_light *light)
{
	if (!light)
		return ;
	free(light->point);
	light->point = NULL;
}
