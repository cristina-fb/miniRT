/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 19:27:14 by crisfern          #+#    #+#             */
/*   Updated: 2022/12/01 17:41:05 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

float	vector_module(t_coord a)
{
	return (sqrt(pow(a.x, 2.0) + pow(a.y, 2.0) + pow(a.z, 2.0)));
}

float	dot_product(t_coord a, t_coord b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_coord	vector_product(t_coord a, t_coord b)
{
	t_coord	result;

	result.x = (a.y * b.z) - (a.z * b.y);
	result.y = (a.z * b.x) - (a.x * b.z);
	result.z = (a.x * b.y) - (a.y * b.x);
	return (result);
}

t_coord	unit_vector(t_coord v)
{
	float	denominator;

	denominator = vector_module(v);
	return (vector_div(v, denominator));
}
