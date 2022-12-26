/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coords_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 17:18:36 by jalvarad          #+#    #+#             */
/*   Updated: 2022/12/26 17:58:24 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

/* returns a t_coord pointer to t_coord struct*/
void	save_coords(t_coord *coord, char **floats_buf, bool *err)
{
	coord->x = ft_mod_atof(floats_buf[0], err);
	coord->y = ft_mod_atof(floats_buf[1], err);
	coord->z = ft_mod_atof(floats_buf[2], err);
}

t_coord	*get_coords(char *str_coords)
{
	char	**floats_buf;
	t_coord	*return_coord;
	bool	err;

	floats_buf = ft_split(str_coords, ',');
	err = false;
	if (!floats_buf)
		return (NULL);
	else if (!str_is_float(floats_buf[0]) || !str_is_float(floats_buf[1]) || \
			!str_is_float(floats_buf[2]))
		err = true;
	return_coord = ft_calloc(1, sizeof(t_coord));
	if (!return_coord)
		err = true;
	else
		save_coords(return_coord, floats_buf, &err);
	ft_free_matrix(floats_buf);
	if (err)
	{
		free(return_coord);
		return (NULL);
	}
	return (return_coord);
}

t_coord	*orientation_vector(char *str_cords)
{
	t_coord	*coord;

	coord = get_coords(str_cords);
	if (coord)
	{
		if (coord->x < -1.00 || coord->x > 1.00 || coord->y < -1.00 || \
			coord->y > 1.00 || coord->z < -1.00 || coord->z > 1.00)
		{
			free(coord);
			coord = NULL;
		}
	}
	return (coord);
}
