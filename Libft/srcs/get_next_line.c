/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:08:39 by jalvarad          #+#    #+#             */
/*   Updated: 2022/09/19 17:08:56 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_returns(ssize_t n_bytes, char **save, char **line)
{
	char	*temp;
	char	*temp2;

	if (!n_bytes && !*save)
		*line = ft_strdup("");
	else if (ft_strchr(*save, '\n'))
	{
		temp = ft_strchr(*save, '\n');
		*temp = '\0';
		*line = ft_strdup(*save);
		temp2 = ft_strdup (temp + 1);
		free(*save);
		*save = temp2;
		return (1);
	}
	else
	{
		*line = ft_strdup(*save);
		free(*save);
		*save = NULL;
	}
	return (0);
}

static void	ft_save(char **save, char *buffer, int fd)
{
	char	*tmp;

	if (!save[fd])
		save[fd] = ft_strdup(buffer);
	else
	{
		tmp = ft_strjoin(save[fd], buffer);
		free(save[fd]);
		save[fd] = tmp;
	}
}

int	get_next_line(int fd, char **line)
{
	char			buffer[BUFFER_SIZE + 1];
	static char		*save[FD_SETSIZE];
	int				n_bytes;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	n_bytes = read(fd, buffer, BUFFER_SIZE);
	if (n_bytes == -1)
		return (-1);
	while (n_bytes > 0)
	{
		buffer[n_bytes] = '\0';
		ft_save(save, buffer, fd);
		if (ft_strchr(save[fd], '\n'))
			break ;
		n_bytes = read(fd, buffer, BUFFER_SIZE);
		if (n_bytes == -1)
		{
			free(*save);
			return (-1);
		}
	}
	return (ft_returns(n_bytes, &save[fd], *&line));
}
