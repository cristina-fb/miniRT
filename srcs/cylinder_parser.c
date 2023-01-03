/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:30:06 by jalvarad          #+#    #+#             */
/*   Updated: 2023/01/03 20:38:16 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	get_cylinder_data(t_cylinder *cylinder, t_program *program)
{
	bool	err;

	err = false;
	cylinder->center = get_coords(program->attr_buf[1]);
	cylinder->vector = orientation_vector(program->attr_buf[2]);
	cylinder->diameter = ft_mod_atof(program->attr_buf[3], &err);
	cylinder->height = ft_mod_atof(program->attr_buf[4], &err);
	cylinder->rgb = get_rgb(program->attr_buf[5], &err);
	if (!cylinder->center || !cylinder->vector || err || !cylinder->rgb)
	{
		cylinder_cleaner(cylinder);
		return (false);
	}
	return (true);
}

static bool	cylinder_basic_parse(t_program *program)
{
	return (ft_word_count(program->attr_buf[1], ',') != 3 || \
		ft_word_count(program->attr_buf[2], ',') != 3 || \
		!str_is_float(program->attr_buf[3]) || \
		!str_is_float(program->attr_buf[4]) || \
		ft_word_count(program->attr_buf[5], ',') != 3);
}

bool	parse_cylinder(t_program *program)
{
	t_cylinder	*cylinder;
	t_list		*new;

	if (cylinder_basic_parse(program))
		return (false);
	cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
		return (false);
	*cylinder = (t_cylinder){NULL, NULL, NULL, NULL, 0.00, 0.00, 0.00, NULL};
	if (!get_cylinder_data(cylinder, program))
		return (false);
	new = ft_mod_lstnew(CYLINDER, cylinder);
	if (!new)
		return (false);
	ft_lstadd_back(&program->geometries, new);
	return (true);
}
