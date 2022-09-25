/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 16:25:32 by jalvarad          #+#    #+#             */
/*   Updated: 2022/09/25 13:47:22 by jalvarad         ###   ########.fr       */
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