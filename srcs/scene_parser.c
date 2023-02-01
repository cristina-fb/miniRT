/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:00:31 by jalvarad          #+#    #+#             */
/*   Updated: 2023/01/26 12:24:18 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	parse_light(t_program *program)
{
	bool	err;

	err = false;
	if (program->light)
		return (false);
	program->light = ft_calloc(1, sizeof(t_light));
	if (!program->light)
		return (false);
	program->light[0] = (t_light){NULL, NULL, 0.00};
	if (ft_word_count(program->attr_buf[1], ',') != 3 || \
		!str_is_float(program->attr_buf[2]) || \
		ft_word_count(program->attr_buf[3], ',') != 3)
		return (false);
	program->light->point = get_coords(program->attr_buf[1]);
	program->light->ratio = ft_mod_atof(program->attr_buf[2], &err);
	program->light->rgb = get_rgb(program->attr_buf[3], &err);
	if (err || not_in_ambient_ratio(program->light->ratio))
		light_cleaner(program->light);
	return (err == false);
}

bool	parse_camera(t_program *program)
{
	bool		err;

	err = false;
	if (program->camera)
		return (false);
	program->camera = ft_calloc(1, sizeof(t_camera));
	if (!program->camera)
		return (false);
	program->camera[0] = (t_camera){NULL, NULL, NULL, NULL, NULL, 0.00, 0, 0};
	if (ft_word_count(program->attr_buf[1], ',') != 3 || \
		ft_word_count(program->attr_buf[2], ',') != 3 || \
		!str_is_float(program->attr_buf[3]))
		return (false);
	program->camera->center = get_coords(program->attr_buf[1]);
	program->camera->orientation = orientation_vector(program->attr_buf[2]);
	program->camera->fov = ft_mod_atof(program->attr_buf[3], &err);
	if (!program->camera->center || !program->camera->orientation || \
		err || is_not_fov(program->camera->fov))
		camera_cleaner(program->camera);
	return (err == false);
}

bool	parse_ambient_ligth(t_program *program)
{
	bool	err;

	err = false;
	if (program->ambient)
		return (false);
	program->ambient = ft_calloc(1, sizeof(t_ambient));
	if (!program->ambient)
		return (false);
	program->ambient[0] = (t_ambient){NULL, 0.00};
	if (!str_is_float(program->attr_buf[1]) && \
		ft_word_count(program->attr_buf[2], ',') != 3)
		return (false);
	program->ambient->ratio = ft_mod_atof(program->attr_buf[1], &err);
	program->ambient->rgb = get_rgb(program->attr_buf[2], &err);
	if (err || not_in_ambient_ratio(program->ambient->ratio))
		ambient_light_cleaner(program->ambient);
	return (err == false);
}
