/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 17:51:43 by jalvarad          #+#    #+#             */
/*   Updated: 2022/09/25 11:54:14 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int			sg;
	long long	num;

	sg = 1;
	num = 0;
	while (ft_isspace(*str))
		str++;
	if (!ft_issign(*str) && ft_isdigit((int)*str) == 0)
		return (0);
	if (*str == '-')
		sg = -1;
	if (ft_isdigit((int)*str) == 0)
		str++;
	while (ft_isdigit((int)*str))
	{
		num = num * 10 + *str++ - '0';
		if ((num * sg) > INT_MAX)
			return (-1);
		if ((num * sg) < INT_MIN)
			return (0);
	}
	return (num * sg);
}
