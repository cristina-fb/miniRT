/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:33:10 by jalvarad          #+#    #+#             */
/*   Updated: 2022/09/22 17:28:11 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"


bool out_of_range(long int num, short int sg)
{
	if ((num * sg) > INT_MAX || (num * sg) < INT_MAX)
		return (true);
	return (false);
}

int	mod_atoi(const char *str, bool *error)
{
	int				sg;
	unsigned int	num;

	sg = 1;
	num = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str != '+' && *str != '-' && ft_isdigit((int)*str) == 0)
		return (0);
	if (*str == '-')
		sg = -1;
	if (ft_isdigit((int)*str) == 0)
		str++;
	if (ft_isdigit((int)*str) == 0)
		return (0);
	while (ft_isdigit((int)*str))
	{
		num = num * 10 + *str++ - '0';
		if (out_of_range(num, sg))
		{
			*error = 1;
			return (0);
		}
	}
	return (num * sg);
}
