/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalvarad <jalvarad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:47:53 by jalvarad          #+#    #+#             */
/*   Updated: 2023/02/04 17:01:09 by jalvarad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int horizontal_resolution(void)
{
	int horizontal_resolution;
	
	horizontal_resolution = ((float)16 / 9) * RESOLUTION ; //widescreen 16:9
	return (horizontal_resolution);
}