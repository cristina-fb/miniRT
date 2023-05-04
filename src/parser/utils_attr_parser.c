/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_attr_parser.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:25:32 by jalvarad          #+#    #+#             */
/*   Updated: 2023/05/04 18:20:56 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool	not_in_ambient_ratio(float ratio)
{
	return (ratio < 0.00 || ratio > 1.00);
}

bool	is_not_fov(float fov)
{
	return (fov < 0.00 || fov > 180.00);
}

static short int	is_rt_element(char **attr_buf)
{
	size_t	m_len;
	size_t	str_len;

	if (!attr_buf)
		return (-1);
	m_len = ft_matrix_len(attr_buf);
	str_len = ft_strlen(attr_buf[0]);
	if (!ft_strncmp(attr_buf[0], "A", str_len) && m_len == N_DATA_A)
		return (AMBIENT_LIGTH);
	else if (!ft_strncmp(attr_buf[0], "C", str_len) && m_len == N_DATA_CA)
		return (CAMERA);
	else if (!ft_strncmp(attr_buf[0], "L", str_len) && m_len == N_DATA_L)
		return (LIGHT);
	else if (!ft_strncmp(attr_buf[0], "cy", str_len) && m_len == N_DATA_CY)
		return (CYLINDER);
	else if (!ft_strncmp(attr_buf[0], "pl", str_len) && m_len == N_DATA_P)
		return (PLANE);
	else if (!ft_strncmp(attr_buf[0], "sp", str_len) && m_len == N_DATA_SP)
		return (SPHERE);
	else if (!ft_strncmp(attr_buf[0], "t", str_len) && m_len == N_DATA_T)
		return (TORUS);
	return (-1);
}

bool	are_basic_attr(t_program program)
{
	return (program.ambient && program.camera && program.light);
}

t_program	get_attributes(char **all_file, bool *error)
{
	t_program		program;
	unsigned int	i;
	short int		element;
	t_action		function[N_TYPES];

	program = (t_program){NULL, NULL, NULL, NULL, NULL, 0, 0, 0, 0};
	i = -1;
	parsers_charge(function);
	while (all_file[++i] && !*error)
	{
		program.attr_buf = ft_split(all_file[i], ' ');
		element = is_rt_element(program.attr_buf);
		*error = true;
		if (element >= 0)
			*error = !function[element](&program);
		ft_free_matrix(program.attr_buf);
	}
	if (*error)
		free_program_data(&program, true);
	return (program);
}
