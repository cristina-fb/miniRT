/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: crisfern <crisfern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 17:17:34 by crisfern          #+#    #+#             */
/*   Updated: 2023/02/02 12:54:46 by crisfern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_coord	vector_add(t_coord a, t_coord b)
{
	t_coord	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_coord	vector_sub(t_coord a, t_coord b)
{
	t_coord	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_coord	vector_mul(t_coord a, float b)
{
	t_coord	result;

	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;
	return (result);
}

t_coord	vector_div(t_coord a, float b)
{
	t_coord	result;

	result.x = a.x / b;
	result.y = a.y / b;
	result.z = a.z / b;
	return (result);
}
