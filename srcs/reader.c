/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 18:14:08 by jalvarad          #+#    #+#             */
/*   Updated: 2022/12/10 17:19:06 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* This function returns a resized matrix adding the new_str, 
and set free the old matrix*/
static char **resize_matrix(char **matrix, char *new_str)
{
	unsigned int	i; 
	char			**new_matrix;

	i = -1;
	if (!matrix)
		matrix = (char **)ft_calloc(1, sizeof(char*));
	new_matrix = (char **)ft_calloc(ft_matrix_len(matrix) + 2, sizeof(char*));
	if (!new_matrix)
		return (NULL);
	while (matrix[++i])
		new_matrix[i] = matrix[i];
	new_matrix[i] = new_str;
	free(matrix);
	return(new_matrix);
}

/* This function returns every line in a matrix */
char** read_file( int fd)
{
	char *line;
	char **new_matrix;
	char **old_matrix;

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
