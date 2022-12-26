/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:19:51 by jalvarad          #+#    #+#             */
/*   Updated: 2022/12/26 17:42:33 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	get_sphere_data(t_sphere *sphere, t_program *program)
{
	bool	err;

	err = false;
	sphere->center = get_coords(program->attr_buf[1]);
	sphere->diameter = ft_mod_atof(program->attr_buf[2], &err);
	sphere->rgb = get_rgb(program->attr_buf[3], &err);
	if (!sphere->center || err || !sphere->rgb)
	{
		sphere_cleaner(sphere);
		return (false);
	}
	return (true);
}

static bool	sphere_basic_parse(t_program *program)
{
	return (ft_word_count(program->attr_buf[1], ',') != 3 || \
		!str_is_float(program->attr_buf[2]) || \
		ft_word_count(program->attr_buf[3], ',') != 3);
}

bool	parse_sphere(t_program *program)
{
	t_sphere	*sphere;
	t_list		*new;

	if (sphere_basic_parse(program))
		return (false);
	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (false);
	*sphere = (t_sphere){NULL, 0.00, 0.00, NULL};
	if (!get_sphere_data(sphere, program))
		return (false);
	new = ft_mod_lstnew(SPHERE, sphere);
	if (!new)
		return (false);
	ft_lstadd_back(&program->geometries, new);
	return (true);
}
