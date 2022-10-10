/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:25:32 by jalvarad          #+#    #+#             */
/*   Updated: 2022/10/10 18:51:14 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

bool file_format(char *file_name)
{
	short int start_sufix;
	short int str_len;

	str_len = ft_strlen(file_name);
	start_sufix = str_len - 3;
	if (start_sufix >= 0 && str_len > 3)
		return (!ft_strncmp(file_name + start_sufix, ".rt", 3));
	return (false);
}
/* this function returns char ** with the RGB */
/* solo retorna NULL en caso de fallo de malloc */

short int *save_rgb(char **rgb_buf, bool *err)
{
	short int *rgb;
	short int i;

	rgb = ft_calloc(3, sizeof(short int));
	i = -1;
	if (!rgb)
	{
		*err = true;
		return (NULL);
	}
	rgb[0] = ft_mod_atoi(rgb_buf[0], err);
	rgb[1] = ft_mod_atoi(rgb_buf[1], err);
	rgb[2] = ft_mod_atoi(rgb_buf[2], err);
	while (++i < 3 && !*err)
		*err = (rgb[i] < 0 || rgb[i] > 255);
	return (rgb);
}

short int *get_rgb(char **attr_buf, bool *err)
{
	char *rgb_buf;
	short int *rgb;

	rgb_buf = ft_split(attr_buf[2], ',');
	if (!str_is_int(rgb_buf[0]) || !str_is_int(rgb_buf[1])
		 || !str_is_int(rgb_buf[2]))
		*err = true;
	rgb = get_rgb(rgb_buf, err);
	ft_free_matrix(rgb_buf);
	return (rgb);
}

// create function to get bright_ratio
/*this functions returns true on success*/

bool parse_ambient_ligth(t_program *program, char **attr_buf)
{
	t_ambient	a_light;
	bool		err;

	err = false;
	if (!str_is_float(attr_buf[1]) && ft_word_count(attr_buf[2], ',') != 3)
		return (false);
	a_light.ratio = ft_mod_atof(attr_buf[1], &err);
	if (err && (a_light.ratio < 0.00 || a_light.ratio > 1.00))
		return (false);
	a_light.rgb = get_rgb(attr_buf, &err);
	if (err)
	{
		free(a_light.rgb);
		return (false);
	}
	program->ambient = (t_ambient*)ft_calloc(1, sizeof(t_ambient));
	if(!program->ambient)
		return (false);
	program->ambient[0] = a_light;
	return (true);
}

bool parse_camera(t_program *program, char **attr_buf)
{
	return (true);
}

bool parse_light(t_program *program, char **attr_buf)
{
	return (true);
}

bool parse_cylinder(t_program *program, char **attr_buf)
{
	return (true);
}

bool parse_plane(t_program *program, char **attr_buf)
{
	return (true);
}

bool parse_sphere(t_program *program, char **attr_buf)
{
	return (true);
}

short int is_rt_element(char **attr_buf)
{
	size_t m_len;
	size_t str_len;

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
	else if (!ft_strncmp(attr_buf[0], "p", str_len) && m_len == N_DATA_P)
		return (PLANE);
	else if (!ft_strncmp(attr_buf[0], "sp", str_len) && m_len == N_DATA_SP)
		return (SPHERE);
	return (-1);
}

t_program get_attributes(char **all_file, bool *error)
{
	t_program program;
	unsigned int i;
	short int element;

	program = (t_program){NULL, NULL, NULL, NULL, NULL, NULL, 0, 0};
	bool (*function[6])(t_program *);
	function[AMBIENT_LIGTH] = parse_ambient_ligth;
	function[CAMERA] = parse_camera;
	function[LIGHT] = parse_light;
	function[CYLINDER] = parse_cylinder;
	function[PLANE] = parse_plane;
	function[SPHERE] = parse_sphere;
	i = -1;
	while(all_file[++i] && !error)
	{
		program.attr_buf = ft_split(all_file[i], ' ');
		element = is_rt_element(program.attr_buf);
		if (element < 0)
			*error = true;
		*error = !function[element](&program);
		ft_free_matrix(program.attr_buf);
	}
	//function  to free all and return ---- falta hcerla
	return (program);
}
