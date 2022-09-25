/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_str_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 13:39:45 by jalvarad          #+#    #+#             */
/*   Updated: 2022/09/25 13:40:06 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	str_is_int(const char *str)
{
	if (ft_issign(*str))
		str++;
	if (!ft_isdigit(*str))
		return (false);
	while (ft_isdigit(*str))
		str++;
	if(!ft_isdigit(*str) && *str)
		return (false);
	return (true);
}

bool	str_is_float(const char * str)
{
	if (ft_issign(*str))
		str++;
	if (!ft_isdigit(*str))
		return (false);
	while (ft_isdigit(*str))
		str++;
	if (*str == '.')
	{
		str++;
		if (!ft_isdigit(*str))
			return (false);
	}
	while (ft_isdigit(*str))
		str++;
	if(!ft_isdigit(*str) && *str)
		return (false);
	return (true);
}
