/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mod_atof.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 11:32:21 by jalvarad          #+#    #+#             */
/*   Updated: 2022/12/26 14:56:03 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static double	absolute_float(const char *str, bool *out_of_range)
{
	bool	after_dot;
	float	scale;
	double	num;

	after_dot = 0;
	scale = 1;
	num = 0;
	while ((*str == '.' || ft_isdigit(*str)) && !*out_of_range)
	{
		if (after_dot)
		{
			scale /= 10;
			num += (*str - '0') * scale;
		}
		else
		{
			if (*str == '.')
				after_dot++;
			else
				num = num * 10.0 + (*str - '0');
			*out_of_range = num > INT_MAX;
		}
		str++;
	}
	return (num);
}

/*el numero que llegue aquí vendrá parseado previamente con 
formato de float (espacios signo numero punto numero espacios)*/

double	ft_mod_atof(const char *str, bool *out_of_range)
{
	double	num;
	bool	sg;

	sg = 0;
	*out_of_range = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
		sg = 1;
	if (ft_isdigit((int)*str) == 0)
		str++;
	num = absolute_float(str, out_of_range);
	if (sg)
		return (-num);
	return (num);
}
