/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 18:14:08 by jalvarad          #+#    #+#             */
/*   Updated: 2022/12/26 15:16:35 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* This function returns a resized matrix adding the new_str, 
and set free the old matrix*/
static char	**resize_matrix(char **matrix, char *new_str)
{
	unsigned int	i;
	char			**new_matrix;

	i = -1;
	if (!matrix)
		matrix = (char **)ft_calloc(1, sizeof(char *));
	new_matrix = (char **)ft_calloc(ft_matrix_len(matrix) + 2, sizeof(char *));
	if (!new_matrix)
		return (NULL);
	while (matrix[++i])
		new_matrix[i] = matrix[i];
	new_matrix[i] = new_str;
	free(matrix);
	return (new_matrix);
}

/* This function returns every line of file in a matrix */
static char	**read_file( int fd)
{
	char	*line;
	char	**new_matrix;
	char	**old_matrix;

	old_matrix = NULL;
	new_matrix = NULL;
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strlen(line))
		{
			new_matrix = resize_matrix(old_matrix, line);
			old_matrix = new_matrix;
		}
		else
			free(line);
		line = NULL;
	}
	free(line);
	return (new_matrix);
}

char	**open_read(char *file_name, char **err_message)
{
	char	**file;
	int		fd;

	file = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		*err_message = ft_strdup(ERR_C);
	else
		file = read_file(fd);
	close(fd);
	return (file);
}
