/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:25:32 by jalvarad          #+#    #+#             */
/*   Updated: 2022/10/01 20:06:21 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
typedef bool (*function[6])(t_program *);
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

bool parse_ambient_ligth(t_program *program)
{
	return (true);
}

bool parse_camera(t_program *program)
{
	return (true);
}

bool parse_light(t_program *program)
{
	return (true);
}

bool parse_cylinder(t_program *program)
{
	return (true);
}

bool parse_plane(t_program *program)
{
	return (true);
}

bool parse_sphere(t_program *program)
{
	return (true);
}

t_program get_attributes(char **all_file, bool *error)
{
	t_program program;
	unsigned int i;
	char **attr_buffer;
	short int element;

	program = (t_program){NULL, NULL, NULL, NULL, NULL, 0, 0};
	bool (*function[6])(t_program *);
	function[AMBIENT_LIGTH] = parse_ambient_ligth;
	function[CAMERA] = parse_camera;
	function[LIGHT] = parse_light;
	function[CYLINDER] = parse_cylinder;
	function[PLANE] = parse_plane;
	function[SPHERE] = parse_sphere;
	i = -1;
	while(all_file[i] && !error)
	{
		attr_buffer = ft_split(all_file[i], ' ');
		element = is_rt_element(attr_buffer);//// hacer esta funcion
		if (element < 0)
			*error = true;//function  to free all and return ---- falta hacer
		*error = function[element](&program);//llamar a la funcioon de antes
		ft_free_matrix(attr_buffer);
		i++;
	}
	return (program);
}
