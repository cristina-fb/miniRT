/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:25:32 by jalvarad          #+#    #+#             */
/*   Updated: 2022/09/22 18:32:06 by jalvarad         ###   ########.fr       */
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
	return false;
}

/*char **read_all_file(unsigned short int fd)
{
	char *all_file;
	char *line;
	char *buffer;

	all_file = ft_strdup("");
	while (get_next_line(fd, &line) > 0)
	{
		buffer = ft_strjoin(all_file, line);
		free(all_file);
		free(line);
		all_file = ft_strjoin(buffer, "\n");
		free(buffer);
	}
	free(line);
	return (all_file);
}*/

double absolute_float(const char *str)
{
	bool	after_dot;
	float	scale;
	double	num;

	after_dot = 0;
	while (*str)
	{
		if (after_dot)
		{
			scale = scale/10;
			num += (*str - '0') * scale;
		}
		else
		{
			if (*str == '.')
				after_dot++;
			else
				num *= 10.0 + (*str - '0');
		}
		str++;
	}
	return (num);
}

double mod_atof(const char *str)
{
	double	num;
	bool	sg;

	sg = 0;
	if (*str == '-')
		sg = 1;
	str++;
	num = absolute_float(str);
	if (sg)
		return (-num);
	return num;
}
