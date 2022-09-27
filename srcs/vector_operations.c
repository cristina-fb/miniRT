/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:17:34 by crisfern          #+#    #+#             */
/*   Updated: 2022/09/27 16:25:50 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	vector_module(t_coord *a, t_coord *b)
{
	return (sqrt(pow(a->x - b->x, 2.0) + pow(a->y - b->y, 2.0) + pow(a->z - b->z, 2.0)));
}

t_coord	vector_sub(t_coord *a, t_coord *b)
{
	t_coord	result;

	result.x = a->x - b->x;
	result.y = a->y - b->y;
	result.z = a->z - b->z;
	return (result);
}

float	dot_product(t_coord *a, t_coord *b)
{
	return ((a->x * b->x) + (a->y * b->y) + (a->z * b->z));
}
